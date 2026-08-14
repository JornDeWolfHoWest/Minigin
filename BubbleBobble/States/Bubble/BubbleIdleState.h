#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class BubbleIdleState final : public State
	{
	public:
		explicit BubbleIdleState(GameObject* owner);
		~BubbleIdleState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;

	private:
		float m_popTimer{ 0.0f };
		float m_popTime{ 5.0f };
		float m_passedTime{ 0.0f };
	};
}