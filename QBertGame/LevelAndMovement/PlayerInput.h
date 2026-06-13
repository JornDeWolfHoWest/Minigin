#pragma once
#include <BaseComponent.h>

#include "InputManager.h"
#include "MovementSystem.h"

namespace game
{
	enum class Player : int
	{
		Player1 = 0,
		Player2 = 1,
		Player3 = 2,
		Player4 = 3
	};
	class MovementSystem;

	enum class InputType : int
	{
		Keyboard = 0,
		Controller = 1
	};

	class PlayerInputSetup : public dae::BaseComponent
	{
	public:
		PlayerInputSetup(dae::GameObject* owner, Player player);
		virtual ~PlayerInputSetup() = default;

		void Update(const float&) override {};
		void FixedUpdate() override {}
		void Render() const override {}


		static void SetPlayer1(InputType input);
		static void SetPlayer2(InputType input);
		static InputType GetPlayer1();
		static InputType GetPlayer2();

	private:
		void KeyboardInput();
		void ControllerInput();

		MovementSystem* m_Movement;
		game::Player m_Player;
		InputType m_InputType;

		static InputType m_Player1;
		static InputType m_Player2;


		bool m_IsMovingInput{};
		Direction m_InputDirection{ Direction::Down };
	};
}
