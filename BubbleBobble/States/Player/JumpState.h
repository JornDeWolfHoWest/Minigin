#pragma once
#include "BubbleBobble/States/StateComponent.h"
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"

namespace dae
{
	class JumpState final : public State
	{
	public:
		explicit JumpState(GameObject* owner, int playerNumber);

		~JumpState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;
	private:
		int m_playerNumber{};
		AnimationComponent* m_animationComponent{};
		RigidBodyComponent* m_rb{};
	};
}