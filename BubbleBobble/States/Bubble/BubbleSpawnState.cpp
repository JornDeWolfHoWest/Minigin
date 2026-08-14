#include "BubbleSpawnState.h"
#include "AnimationComponent.h"
#include "BubbleBobble/Bubble/BubbleComponent.h"
#include "BubbleBobble/Bubble/BubbleEventHandler.h"
#include "GameObject.h"

dae::BubbleSpawnState::BubbleSpawnState(GameObject* owner) :
	State(owner)
{}

void dae::BubbleSpawnState::OnEnter()
{
	GetOwner()->GetComponent<BubbleComponent>()->SetIsAvailable(true);
	if (auto eventHandler = GetOwner()->GetComponent<BubbleEventHandlerComponent>())
	{
		eventHandler->OnBubbleSpawn();
	}

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubbleIdle");
	}

	GetOwner()->SetLocalPosition(-100.0f, -100.0f, 0.0f);
}

void dae::BubbleSpawnState::OnExit()
{}

void dae::BubbleSpawnState::Update(const float& /*deltaTime*/)
{}