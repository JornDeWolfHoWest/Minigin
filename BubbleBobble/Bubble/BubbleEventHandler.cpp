#include <iostream>
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "BubbleEventHandler.h"
#include "BubbleBobble/States/Bubble/BubblePopState.h"
#include "BubbleBobble/States/Bubble/BubbleSpawnState.h"
#include "BubbleBobble/States/ZenChan/ZenChanVulnerableState.h"
#include "BubbleBobble/States/StateComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"


dae::BubbleEventHandlerComponent::BubbleEventHandlerComponent(GameObject* owner)
	: BaseComponent(owner)
{}

void dae::BubbleEventHandlerComponent::Update(const float& /*deltaTime*/)
{}

void dae::BubbleEventHandlerComponent::OnBubbleHitEnemy(GameObject* bubble, GameObject* hitEnemy)
{
	auto bubbleStateComp = bubble->GetComponent<StateComponent>();
	bubbleStateComp->SetState("Spawn");

	auto enemyStateComp = hitEnemy->GetComponent<StateComponent>();

	enemyStateComp->SetState("Vulnerable");
}

void dae::BubbleEventHandlerComponent::OnBubblePopNoEnemy(GameObject* bubble)
{
	auto stateComp = bubble->GetComponent<StateComponent>();
	stateComp->SetState("Pop");
}

void dae::BubbleEventHandlerComponent::OnBubbleSpawn()
{
}

void dae::BubbleEventHandlerComponent::OnBubbleShot()
{}

void dae::BubbleEventHandlerComponent::OnBubblePlayerJump(GameObject* player, GameObject* bubble)
{
	player->GetComponent<StateComponent>()->SetState("Jump");
	bubble->GetComponent<StateComponent>()->SetState("Spawn");
}

#include "BubbleBobble/Enemy/ZenChanComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"

void dae::BubbleEventHandlerComponent::OnCollision(ColliderComponent* self, ColliderComponent* other)
{
	if (other == self) return; // Ignore self-collision if it ever occurs

	if (!GetOwner()) return;
	auto bubbleStateComp = GetOwner()->GetComponent<StateComponent>();
	if (!bubbleStateComp) return;

	if (other->GetGameObject()->GetComponent<ZenChanComponent>())
	{
		OnBubbleHitEnemy(GetOwner(), other->GetGameObject());
		return;
	}


	auto playerComp = other->GetGameObject()->GetComponent<PlayerComponent>();
	if (playerComp) // Check if it's a collidor
	{
		if (other->GetGameObject()->GetComponent<RigidBodyComponent>()->GetVerticalVelocity() > 0)
			OnBubblePlayerJump(other->GetGameObject(), GetOwner());
		else
			OnBubblePopNoEnemy(GetOwner());
		return;
	}
}