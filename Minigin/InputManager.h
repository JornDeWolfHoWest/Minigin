#pragma once

#include "Singleton.h"

#include <SDL3/SDL.h>
#include <Windows.h>
#include <Xinput.h>

#include <functional>
#include <memory>
#include <vector>

namespace dae
{
	class ControllerButtonCommand final
	{
	public:
		ControllerButtonCommand(
			int buttonToPress,
			int controllerIndex,
			std::function<void()> downCommand = {},
			std::function<void()> upCommand = {}
		);

		void Execute(WORD buttonsPressed, int controllerIndex);

	private:
		bool m_IsPressed{ false };

		int m_KeyToPress{};
		int m_ControllerIndex{};

		std::function<void()> m_DownCommand{};
		std::function<void()> m_UpCommand{};
	};

	class KeyCommand final
	{
	public:
		KeyCommand(
			SDL_Keycode keyPressed,
			std::function<void()> downCommand = {},
			std::function<void()> upCommand = {}
		);

		void DownExecute(SDL_Keycode keyPressed) const;
		void UpExecute(SDL_Keycode keyPressed) const;

	private:
		SDL_Keycode m_KeyToPress{};

		std::function<void()> m_DownCommand{};
		std::function<void()> m_UpCommand{};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() = default;

		bool ProcessInput();

		void DeleteAllKeys();
		void DeleteAllKeyboardKeys();
		void DeleteAllControllerKeys();

		void AddKeyCommand(
			SDL_Keycode key,
			std::function<void()> downCommand = {},
			std::function<void()> upCommand = {}
		);

		void AddControllerKeyCommand(
			int button,
			int controllerIndex,
			std::function<void()> downCommand = {},
			std::function<void()> upCommand = {}
		);

	private:
		friend class Singleton<InputManager>;

		std::vector<std::unique_ptr<KeyCommand>> m_KeyCommands{};
		std::vector<std::unique_ptr<ControllerButtonCommand>> m_ControllerButtonCommands{};

		bool m_BreakCommands{ false };
	};
}