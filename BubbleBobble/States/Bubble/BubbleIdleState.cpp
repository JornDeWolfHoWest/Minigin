#include "BubbleIdleState.h"
#include "AnimationComponent.h"
#include "BubblePopState.h"
#include "BubbleBobble/States/StateComponent.h"
#include "GameObject.h"
#include <cmath>

dae::BubbleIdleState::BubbleIdleState(GameObject* owner) : State(owner)
{}

void dae::BubbleIdleState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubbleIdle");
	}
}

void dae::BubbleIdleState::OnExit()
{}

void dae::BubbleIdleState::Update(const float& deltaTime)
{
	m_passedTime += deltaTime;

	glm::vec3 pos = GetOwner()->GetLocalPosition().GetPosition();

	GetOwner()->SetLocalPosition(pos.x, pos.y + std::sin(m_passedTime) * 0.1f, pos.z);

	m_popTimer += deltaTime;
	if (m_popTimer >= m_popTime)
	{
		GetOwner()->GetComponent<StateComponent>()->SetState("Pop");
		m_popTimer = 0;
	}
}