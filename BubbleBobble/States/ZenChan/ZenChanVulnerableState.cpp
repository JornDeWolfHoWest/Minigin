#include "ZenChanVulnerableState.h"

#include <memory>

#include "AnimationComponent.h"
#include "GameObject.h"
#include "BubbleBobble/States/StateComponent.h"
#include "ZenChanChaseState.h"

namespace dae
{
	ZenChanVulnerableState::ZenChanVulnerableState(GameObject* owner) :
		State(owner),
		m_animationComponent(GetOwner()->GetComponent<AnimationComponent>())
	{}

	void ZenChanVulnerableState::OnEnter()
	{
		if (!m_animationComponent)
		{
			m_animationComponent = GetOwner()->GetComponent<AnimationComponent>();
		}

		if (m_animationComponent)
		{
			m_animationComponent->SetCurrentAnimation("Bubble");
		}
	}

	void ZenChanVulnerableState::OnExit()
	{}

	void ZenChanVulnerableState::Update(const float& deltaTime)
	{
		m_respawnTimer += deltaTime;

		if (!m_animationComponent)
		{
			m_animationComponent = GetOwner()->GetComponent<AnimationComponent>();
		}

		if (m_respawnTimer >= m_angryTime && m_animationComponent)
		{
			m_animationComponent->SetCurrentAnimation("AngryBubble");
		}

		if (m_respawnTimer >= m_maxVulnerableTime)
		{
			if (auto stateComp = GetOwner()->GetComponent<StateComponent>())
			{
				stateComp->SetState("Chase");
			}
		}
	}
}