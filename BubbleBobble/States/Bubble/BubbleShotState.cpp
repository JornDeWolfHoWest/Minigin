#include "BubbleShotState.h"
#include "AnimationComponent.h"
#include "BubbleBobble/Bubble/BubbleEventHandler.h"
#include "BubbleBobble/Bubble/BubbleComponent.h"
#include "BubbleIdleState.h"
#include "GameObject.h"
#include <cmath>

namespace dae
{
	BubbleShotState::BubbleShotState(GameObject* owner, GameObject* playerObject, BubbleComponent* bubbleComponent) :
		State(owner),
		m_playerObject{ playerObject },
		m_bubbleComponent(bubbleComponent)
	{}

	void BubbleShotState::OnEnter()
	{
		if (auto eventHandler = GetOwner()->GetComponent<BubbleEventHandlerComponent>())
		{
			eventHandler->OnBubbleShot();
		}

		if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
		{
			animCmp->SetCurrentAnimation("BubbleIdle");
		}

		if (m_bubbleComponent)
		{
			m_bubbleComponent->SetIsAvailable(false);
		}

		m_initialPlayerPos = m_playerObject->GetLocalPosition().GetPosition();

		m_playerForward = m_playerObject->GetComponent<AnimationComponent>()->GetForwardDirection();
		

		const auto bubbleShootPos = m_initialPlayerPos + glm::vec3{ 32.0f, 0.0f, 0.0f } * m_playerForward;
		GetOwner()->SetLocalPosition(bubbleShootPos.x, bubbleShootPos.y, bubbleShootPos.z);
	}

	void BubbleShotState::OnExit()
	{}

	void BubbleShotState::Update(const float& deltaTime)
	{
		if (!m_bubbleComponent) return;

		glm::vec3 pos = GetOwner()->GetLocalPosition().GetPosition();
		auto offset = m_bubbleComponent->GetSpeed() * deltaTime * m_playerForward;

		GetOwner()->SetLocalPosition(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z);

		m_bubbleLifetimeTimer += deltaTime;

		if (std::abs(GetOwner()->GetLocalPosition().GetPosition().x - m_initialPlayerPos.x) >= m_bubbleComponent->GetMoveDistance()
			|| m_bubbleLifetimeTimer >= m_maxBubbleLifetime)
		{
			m_bubbleLifetimeTimer = 0;
			GetOwner()->GetComponent<StateComponent>()->SetState("Idle");
		}
	}
}