#include "ZenChanChaseState.h"

#include <glm/geometric.hpp>

#include "AnimationComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include <SceneManager.h>
#include <Scene.h>
//#include "BubbleBobble/PlayerComponents/PlayerComponent.h"

// Forward declaration if GetRandomFloat() is globally provided
extern float GetRandomFloat();

namespace dae
{
	ZenChanChaseState::ZenChanChaseState(GameObject* owner) :
		State(owner),
		m_ownerRb(GetOwner()->GetComponent<RigidBodyComponent>()),
		m_ownerCollider(GetOwner()->GetComponent<ColliderComponent>()),
		m_animationComponent(GetOwner()->GetComponent<AnimationComponent>())
	{}

	void ZenChanChaseState::OnEnter()
	{
		/*
		if (m_animationComponent)
		{
			m_animationComponent->SetCurrentAnimation("Walk");
		}

		m_chosenPlayer = dae::SceneManager::GetInstance().GetActiveScene()->GetComponent<PlayerComponent>();
		if (m_chosenPlayer)
		{
			const auto playerPos = m_chosenPlayer->GetWorldPosition().GetPosition();
			const auto ownerPos = GetOwner()->GetWorldPosition().GetPosition();

			glm::vec2 diff{ playerPos.x - ownerPos.x, playerPos.y - ownerPos.y };
			if (glm::length(diff) > 0.0001f)
			{
				m_directionToPlayer = glm::normalize(diff);
			}
		}
		*/
	}

	void ZenChanChaseState::OnExit()
	{}

	void ZenChanChaseState::Update(const float& deltaTime)
	{
		// Lazy-fetch components if not set at construction
		if (!m_ownerRb) m_ownerRb = GetOwner()->GetComponent<RigidBodyComponent>();
		if (!m_ownerCollider) m_ownerCollider = GetOwner()->GetComponent<ColliderComponent>();
		if (!m_animationComponent) m_animationComponent = GetOwner()->GetComponent<AnimationComponent>();

		// Decide on an action every decision interval
		m_timeSinceLastDecision += deltaTime;
		if (m_timeSinceLastDecision >= m_decisionInterval)
		{
			m_timeSinceLastDecision = 0.0f;
			DecideNextAction();
		}

		m_angryTimer += deltaTime;
		if (m_angryTimer >= m_timeUntilAngry && m_animationComponent && m_animationComponent->GetCurrentAnimationName() != "AngryWalk")
		{
			m_animationComponent->SetCurrentAnimation("AngryWalk");
			m_speed *= 1.25f;
			m_decisionInterval = 2.0f;
		}

		// Execute actions based on decisions
		if (m_shouldJump)
		{
			Jump();
		}
		else
		{
			if (m_horizontalDirection == glm::vec2{ 1.0f, 0.0f })
			{
				Move(deltaTime, 1.0f);
			}
			else if (m_horizontalDirection == glm::vec2{ -1.0f, 0.0f })
			{
				Move(deltaTime, -1.0f);
			}
		}

		if (m_ownerRb && m_ownerCollider && m_ownerRb->GetVerticalVelocity() > 0.0f)
		{
			m_ownerCollider->Land();
		}

		// Recalculate direction to player
		if (m_chosenPlayer)
		{
			const auto playerPos = m_chosenPlayer->GetWorldPosition().GetPosition();
			const auto ownerPos = GetOwner()->GetWorldPosition().GetPosition();

			glm::vec2 diff{ playerPos.x - ownerPos.x, playerPos.y - ownerPos.y };
			if (glm::length(diff) > 0.0001f)
			{
				m_directionToPlayer = glm::normalize(diff);
			}
		}
	}

	void ZenChanChaseState::DecideNextAction()
	{
		m_shouldJump = (m_directionToPlayer.y < 0.0f) || (GetRandomFloat() < 0.02f);

		if (!m_shouldJump)
		{
			if (GetRandomFloat() < 0.85f)
			{
				m_horizontalDirection = (GetRandomFloat() < 0.5f) ? glm::vec2{ 1.0f, 0.0f } : glm::vec2{ -1.0f, 0.0f };
			}
			else
			{
				// Todo make him go to player properly
				m_horizontalDirection = (m_directionToPlayer.x > 0.0f) ? glm::vec2{ 1.0f, 0.0f } : glm::vec2{ -1.0f, 0.0f };
			}
		}
		else
		{
			m_horizontalDirection = { 0.0f, 0.0f };
		}
	}

	void ZenChanChaseState::Move(float dt, float dir)
	{
		const auto pos = GetOwner()->GetLocalPosition().GetPosition();
		GetOwner()->SetLocalPosition(pos.x + (m_speed * dt * dir), pos.y, pos.z);

		if (m_animationComponent)
		{
			m_animationComponent->SetForwardDirection({ dir, 0.0f, 0.0f });
		}
	}

	void ZenChanChaseState::Jump()
	{
		if (m_ownerRb)
		{
			m_ownerRb->Jump();
		}
		if (m_ownerCollider)
		{
			m_ownerCollider->StartJumping();
		}
	}
}