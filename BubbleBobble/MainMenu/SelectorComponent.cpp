#include "SelectorComponent.h"
#include "GameObject.h"
#include "BubbleBobble/GameSettings.h"
#include "InputManager.h"

namespace dae
{
	SelectorComponent::SelectorComponent(GameObject* owner, int controllerIndex, int totalOptions) :
		BaseComponent(owner),
		m_totalOptions(totalOptions),
		m_controllerIndex(controllerIndex)
	{
		BindInputs(m_controllerIndex);
	}

	void SelectorComponent::BindInputs(int controllerIndex)
	{
		m_controllerIndex = controllerIndex;

		// Keyboard
		InputManager::GetInstance().AddKeyCommand(
			SDLK_DOWN,
			nullptr,
			[this]() { MoveSelection(1); }
		);

		InputManager::GetInstance().AddKeyCommand(
			SDLK_UP,
			nullptr,
			[this]() { MoveSelection(-1); }
		);

		InputManager::GetInstance().AddKeyCommand(
			SDLK_RIGHT,
			nullptr,
			[this]() { Confirm(); }
		);
		InputManager::GetInstance().AddKeyCommand(
			SDLK_KP_ENTER,
			nullptr,
			[this]() { Confirm(); }
		);
		InputManager::GetInstance().AddKeyCommand(
			SDLK_RETURN,
			nullptr,
			[this]() { Confirm(); }
		);

		// Controller Binds
		InputManager::GetInstance().AddControllerKeyCommand(
			XINPUT_GAMEPAD_DPAD_DOWN,
			m_controllerIndex,
			[this]() { MoveSelection(1); }
		);
		InputManager::GetInstance().AddControllerKeyCommand(
			XINPUT_GAMEPAD_DPAD_UP,
			m_controllerIndex,
			[this]() { MoveSelection(-1); }
		);
		InputManager::GetInstance().AddControllerKeyCommand(
			XINPUT_GAMEPAD_A,
			m_controllerIndex,
			[this]() { Confirm(); }
		);
	}

	void SelectorComponent::MoveSelection(int offset)
	{
		m_currentSelection = (m_currentSelection + offset % m_totalOptions + m_totalOptions) % m_totalOptions;

		UpdatePosition();
	}

	void SelectorComponent::UpdatePosition()
	{
		GetOwner()->SetLocalPosition(
			100.0f,
			static_cast<float>(m_currentSelection) * 100.0f + 150.0f,
			0.0f
		);
	}

	void SelectorComponent::Confirm()
	{
		GameSettings::GetInstance().SetGameState(
			static_cast<GameSettings::GameState>(m_currentSelection),
			1
		);
	}
}