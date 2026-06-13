#include "PlayerInput.h"
#include "GameObject.h"
#include "MovementSystem.h"
#include <GameObject.h>
#include <BaseComponent.h>

game::InputType game::PlayerInputSetup::m_Player1 = InputType::Keyboard;
game::InputType game::PlayerInputSetup::m_Player2 = InputType::Keyboard;

game::PlayerInputSetup::PlayerInputSetup(dae::GameObject* owner, Player player) :
	BaseComponent(owner),
	m_Player(player)
{
	switch (m_Player)
	{
	case game::Player::Player1:
		m_InputType = m_Player1;
		break;
	case game::Player::Player2:
		if (m_Player1 != m_Player2)
		{
			m_Player = game::Player::Player1;
		}
		m_InputType = m_Player2;
		break;
	default:
		m_InputType = m_Player2;
	}

	m_Movement = GetOwner()->GetComponent<MovementSystem>();
	if (!m_Movement)
	{
		return;
	}

	switch (m_InputType)
	{
	case InputType::Keyboard:
		KeyboardInput();
		break;
	case InputType::Controller:
		ControllerInput();
		break;
	}
}

void game::PlayerInputSetup::SetPlayer1(InputType input)
{
	m_Player1 = input;
}

void game::PlayerInputSetup::SetPlayer2(InputType input)
{
	m_Player2 = input;
}

game::InputType game::PlayerInputSetup::GetPlayer1()
{
	return m_Player1;
}

game::InputType game::PlayerInputSetup::GetPlayer2()
{
	return m_Player2;
}

void game::PlayerInputSetup::KeyboardInput()
{
	auto startMoveUp = [this]()
		{
			m_Movement->Move(Direction::Up);
		};

	auto startMoveRight = [this]()
		{
			m_Movement->Move(Direction::Right);
		};

	auto startMoveDown = [this]()
		{
			m_Movement->Move(Direction::Down);
		};

	auto startMoveLeft = [this]()
		{
			m_Movement->Move(Direction::Left);
		};

	auto& inputManager = dae::InputManager::GetInstance();

	if (m_Player == game::Player::Player1)
	{
		// Added this so my azety keyboard also works with same keys :)
		inputManager.AddKeyCommand(SDLK_Z, startMoveUp);
		inputManager.AddKeyCommand(SDLK_Q, startMoveLeft);

		// Now for qwerty
		inputManager.AddKeyCommand(SDLK_W, startMoveUp);
		inputManager.AddKeyCommand(SDLK_S, startMoveDown);
		inputManager.AddKeyCommand(SDLK_D, startMoveRight);
		inputManager.AddKeyCommand(SDLK_A, startMoveLeft);

	}
	else // Player 2 will always have arrow keys as input, even if player 1 has controller input
	{
		inputManager.AddKeyCommand(SDLK_UP, startMoveUp);
		inputManager.AddKeyCommand(SDLK_LEFT, startMoveLeft);
		inputManager.AddKeyCommand(SDLK_DOWN, startMoveDown);
		inputManager.AddKeyCommand(SDLK_RIGHT, startMoveRight);
	}
}

void game::PlayerInputSetup::ControllerInput()
{
	auto startMoveUp = [this]()
		{
			m_Movement->Move(Direction::Up);
		};

	auto startMoveRight = [this]()
		{
			m_Movement->Move(Direction::Right);
		};

	auto startMoveDown = [this]()
		{
			m_Movement->Move(Direction::Down);
		};

	auto startMoveLeft = [this]()
		{
			m_Movement->Move(Direction::Left);
		};

	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.AddControllerKeyCommand(
		XINPUT_GAMEPAD_DPAD_UP,
		static_cast<int>(m_Player),
		startMoveUp);

	inputManager.AddControllerKeyCommand(
		XINPUT_GAMEPAD_DPAD_RIGHT,
		static_cast<int>(m_Player),
		startMoveRight);

	inputManager.AddControllerKeyCommand(
		XINPUT_GAMEPAD_DPAD_DOWN,
		static_cast<int>(m_Player),
		startMoveDown);

	inputManager.AddControllerKeyCommand(
		XINPUT_GAMEPAD_DPAD_LEFT,
		static_cast<int>(m_Player),
		startMoveLeft);
}