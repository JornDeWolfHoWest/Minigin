#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class PlayerComponent;

	class IdleState final : public State
	{
	public:
		explicit IdleState(GameObject* owner, int playerNumber, PlayerComponent* playerComponent);

		~IdleState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;

	private:
		int m_playerNumber{};
		PlayerComponent* m_playerComponent{};

	};
}