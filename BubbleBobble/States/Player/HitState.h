#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class HitState final : public State
	{
	public:
		explicit HitState(GameObject* owner, int playerNumber);

		~HitState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;
	private:
		int m_playerNumber{};
		float m_timer{};
		float m_hitDuration{ 3.0f };
	};
}