#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class BubblePopState final : public State
	{
	public:
		explicit BubblePopState(GameObject* owner);
		~BubblePopState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;

	private:
		float m_popTimer{ 0.0f };
		float m_popTime{ 2.0f };
	};
}