#pragma once

#include "BubbleBobble/States/StateComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class AnimationComponent;
	class RigidBodyComponent;
	class ColliderComponent;

	class ZenChanChaseState final : public State
	{
	public:
		explicit ZenChanChaseState(GameObject* owner);
		~ZenChanChaseState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;

	private:
		void DecideNextAction();
		void Move(float dt, float dir);
		void Jump();

		glm::vec2 m_directionToPlayer{ 0.0f, 0.0f };
		RigidBodyComponent* m_ownerRb{ nullptr };
		ColliderComponent* m_ownerCollider{ nullptr };
		GameObject* m_chosenPlayer{ nullptr };
		AnimationComponent* m_animationComponent{ nullptr };

		float m_speed{ 80.0f };
		float m_timeSinceLastDecision{ 2.0f };
		float m_decisionInterval{ 2.0f };
		float m_angryTimer{ 0.0f };
		float m_timeUntilAngry{ 20.0f };
		bool m_shouldJump{ false };
		glm::vec2 m_horizontalDirection{ 0.0f, 0.0f };
	};
}