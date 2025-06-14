#pragma once
#include "Singleton.h"
#include <iostream>
#include <cctype>
#include <SDL.h>
#include <windows.h>
#include <XInput.h>
#include <vector>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "Commands.h"
#pragma comment(lib, "xinput.lib")


namespace dae
{
    class ControllerButtonCommand {
    public:
        ControllerButtonCommand(int buttonToPress, int controllerIndex, Command* downCommand, Command* upCommand)
            : m_DownCommand(downCommand), m_ControllerIndex(controllerIndex), m_UpCommand(upCommand), m_KeyToPress(buttonToPress)
        {
        }
        ~ControllerButtonCommand() {
            delete m_DownCommand;
            delete m_UpCommand;
        }
        void Execute(WORD buttonsPressed, int controllerIndex) {
            if (m_ControllerIndex != -1 and m_ControllerIndex != controllerIndex)
                return;
            if (buttonsPressed & m_KeyToPress)
            {
                if (m_DownCommand != nullptr and not m_IsPressed)
                {
                    m_IsPressed = true;
                    m_DownCommand->execute();
                }
            }
            else if (m_IsPressed)
            {
                m_IsPressed = false;
                if (m_UpCommand != nullptr)
                {
					m_UpCommand->execute();
                }
            }
        }
    private:
		bool m_IsPressed{ false };
        Command* m_DownCommand{};
        Command* m_UpCommand{};
        int m_KeyToPress{};
		int m_ControllerIndex{};
    };
    class KeyCommand {
    public:
        KeyCommand(SDL_Keycode keyPressed, Command* downCommand, Command* upCommand)
            : m_DownCommand(downCommand), m_UpCommand(upCommand), m_KeyToPress(keyPressed)
        {
        }
		~KeyCommand() {
			delete m_DownCommand;
			delete m_UpCommand;
		}
        void DownExecute(SDL_Keycode keyPressed) {
            if (m_KeyToPress == keyPressed)
				if (m_DownCommand != nullptr)
                    m_DownCommand->execute();
        }
        void UpExecute(SDL_Keycode keyPressed) {
            if (m_KeyToPress == keyPressed)
                if (m_UpCommand != nullptr)
                    m_UpCommand->execute();
        }
    private:
        Command* m_DownCommand{};
        Command* m_UpCommand{};
        SDL_Keycode m_KeyToPress{};
    };

	class InputManager final : public Singleton<InputManager>
	{
    public:
        InputManager()
        {
        }

        ~InputManager() {
			for (KeyCommand* command : m_KeyCommands) {
				delete command;
			}
            for (ControllerButtonCommand* command : m_ControllerButtonCommands) {
                delete command;
            }
        }
        void DeleteAllKeys() {
            for (auto key : m_KeyCommands) {
                delete key;
            }
			m_KeyCommands.clear();
            for (auto key : m_ControllerButtonCommands) {
                delete key;
            }
            m_ControllerButtonCommands.clear();
			m_BreakCommands = true;
        }
        void DeleteAllKeyboardKeys() {
            for (auto key : m_KeyCommands) {
                delete key;
            }
            m_KeyCommands.clear();
            m_BreakCommands = true;
        }
        void DeleteAllControllerKeys() {
            for (auto key : m_ControllerButtonCommands) {
                delete key;
            }
            m_ControllerButtonCommands.clear();
            m_BreakCommands = true;
        }

		void AddKeyCommand(KeyCommand* keyCommand) {
			m_KeyCommands.push_back(keyCommand);
		}

        void AddControllerKeyCommand(ControllerButtonCommand* controllerCommand) {
			m_ControllerButtonCommands.push_back(controllerCommand);
        }
        
        bool ProcessInput() {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    return false;
                }
                if (e.type == SDL_KEYDOWN) {
                    for (KeyCommand* command : m_KeyCommands)
                    {
						if (m_BreakCommands) {
							m_BreakCommands = false;
							return true;
						}
						command->DownExecute(e.key.keysym.sym);
                    }
                }
                if (e.type == SDL_KEYUP) {
                    for (KeyCommand* command : m_KeyCommands)
                    {
                        if (m_BreakCommands) {
                            m_BreakCommands = false;
                            return true;
                        }
                        command->UpExecute(e.key.keysym.sym);
                    }
                }
                ImGui_ImplSDL2_ProcessEvent(&e);
            }

            for (int controllerIndex = 0; controllerIndex < 2; controllerIndex++)
            {
                XINPUT_STATE state = {};
                DWORD dwResult = XInputGetState(controllerIndex, &state);
                if (dwResult == ERROR_SUCCESS) {
                    WORD buttons = state.Gamepad.wButtons;

                    for (ControllerButtonCommand* controllerCommand : m_ControllerButtonCommands)
                    {
                        if (m_BreakCommands) {
                            m_BreakCommands = false;
                            return true;
                        }
                        controllerCommand->Execute(buttons, controllerIndex);
                    }
                }
                else {
                    std::cout << "Controller not connected." << std::endl;
                }

            }
            return true;
        }

    private:
		std::vector<ControllerButtonCommand*> m_ControllerButtonCommands{};
        std::vector<KeyCommand*> m_KeyCommands{};
        bool m_BreakCommands{ false };
	};

}
