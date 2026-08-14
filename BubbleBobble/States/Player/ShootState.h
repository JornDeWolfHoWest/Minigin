#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class ShootState final : public State
	{
	public:
		explicit ShootState(GameObject* owner, int playerNumber);

		~ShootState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;
	private:
		int m_playerNumber{};
		float m_timer{};
		float m_hitDuration{ 1.0f };
	};
}