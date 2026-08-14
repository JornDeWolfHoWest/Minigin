#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class FallState final : public State
	{
	public:
		explicit FallState(GameObject* owner, int playerNumber);

		~FallState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;
	private:
		int m_playerNumber{};
	};
}