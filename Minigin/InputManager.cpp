#include "InputManager.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"

#pragma comment(lib, "xinput.lib")

namespace dae
{
	ControllerButtonCommand::ControllerButtonCommand(
		int buttonToPress,
		int controllerIndex,
		std::function<void()> downCommand,
		std::function<void()> upCommand)
		:
		m_KeyToPress(buttonToPress),
		m_ControllerIndex(controllerIndex),
		m_DownCommand(std::move(downCommand)),
		m_UpCommand(std::move(upCommand))
	{}

	void ControllerButtonCommand::Execute(WORD buttonsPressed, int controllerIndex)
	{
		if (m_ControllerIndex != -1 && m_ControllerIndex != controllerIndex)
			return;

		if (buttonsPressed & m_KeyToPress)
		{
			if (!m_IsPressed)
			{
				m_IsPressed = true;

				if (m_DownCommand)
					m_DownCommand();
			}
		}
		else if (m_IsPressed)
		{
			m_IsPressed = false;

			if (m_UpCommand)
				m_UpCommand();
		}
	}

	KeyCommand::KeyCommand(
		SDL_Keycode keyPressed,
		std::function<void()> downCommand,
		std::function<void()> upCommand)
		:
		m_KeyToPress(keyPressed),
		m_DownCommand(std::move(downCommand)),
		m_UpCommand(std::move(upCommand))
	{}

	void KeyCommand::DownExecute(SDL_Keycode keyPressed) const
	{
		if (m_KeyToPress == keyPressed && m_DownCommand)
		{
			m_DownCommand();
		}
	}

	void KeyCommand::UpExecute(SDL_Keycode keyPressed) const
	{
		if (m_KeyToPress == keyPressed && m_UpCommand)
		{
			m_UpCommand();
		}
	}

	void InputManager::DeleteAllKeys()
	{
		m_KeyCommands.clear();
		m_ControllerButtonCommands.clear();

		m_BreakCommands = true;
	}

	void InputManager::DeleteAllKeyboardKeys()
	{
		m_KeyCommands.clear();
	}

	void InputManager::DeleteAllControllerKeys()
	{
		m_ControllerButtonCommands.clear();
	}

	void InputManager::AddKeyCommand(
		SDL_Keycode key,
		std::function<void()> downCommand,
		std::function<void()> upCommand)
	{
		m_KeyCommands.emplace_back(
			std::make_unique<KeyCommand>(
				key,
				std::move(downCommand),
				std::move(upCommand)
			)
		);
	}

	void InputManager::AddControllerKeyCommand(
		int button,
		int controllerIndex,
		std::function<void()> downCommand,
		std::function<void()> upCommand)
	{
		m_ControllerButtonCommands.emplace_back(
			std::make_unique<ControllerButtonCommand>(
				button,
				controllerIndex,
				std::move(downCommand),
				std::move(upCommand)
			)
		);
	}

	bool InputManager::ProcessInput()
	{
		SDL_Event e{};

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
				return false;

			if (e.type == SDL_EVENT_KEY_DOWN)
			{
				for (auto& command : m_KeyCommands)
				{
					command->DownExecute(e.key.key);

					if (m_BreakCommands)
					{
						m_BreakCommands = false;
						return true;
					}
				}
			}

			if (e.type == SDL_EVENT_KEY_UP)
			{
				for (auto& command : m_KeyCommands)
				{
					command->UpExecute(e.key.key);

					if (m_BreakCommands)
					{
						m_BreakCommands = false;
						return true;
					}
				}
			}

			ImGui_ImplSDL3_ProcessEvent(&e);
		}

		for (int controllerIndex = 0; controllerIndex < 2; ++controllerIndex)
		{
			XINPUT_STATE state{};

			if (XInputGetState(controllerIndex, &state) == ERROR_SUCCESS)
			{
				const WORD buttons = state.Gamepad.wButtons;

				for (auto& command : m_ControllerButtonCommands)
				{
					command->Execute(buttons, controllerIndex);

					if (m_BreakCommands)
					{
						m_BreakCommands = false;
						return true;
					}
				}
			}
		}

		return true;
	}
}