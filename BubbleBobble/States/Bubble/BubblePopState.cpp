#include "BubblePopState.h"
#include "AnimationComponent.h"
#include "BubbleSpawnState.h"
#include "BubbleBobble/States/StateComponent.h"
#include "GameObject.h"

dae::BubblePopState::BubblePopState(GameObject* owner) : State(owner)
{}

void dae::BubblePopState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubblePop");
	}
}

void dae::BubblePopState::OnExit()
{}

void dae::BubblePopState::Update(const float& deltaTime)
{
	m_popTimer += deltaTime;
	if (m_popTimer >= m_popTime)
	{
		GetOwner()->GetComponent<StateComponent>()->SetState("Spawn");
		m_popTimer = 0;
	}
}