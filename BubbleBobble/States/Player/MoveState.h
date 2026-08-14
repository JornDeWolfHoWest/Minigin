#pragma once
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class Transform;
	class ColliderComponent;
	class PlayerComponent;

	class MoveState final : public State
	{
	public:
		explicit MoveState(GameObject* owner, int playerNumber, PlayerComponent* playerComponent);

		~MoveState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;
	private:
		int m_playerNumber{};
		AnimationComponent* m_animationComponent{};
		RigidBodyComponent* m_rb{};
		PlayerComponent* m_playerComponent{};
		ColliderComponent* m_collider{};
	};
}