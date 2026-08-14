#include "BubbleComponent.h"
#include "AnimationComponent.h"
#include "BubbleBobble/Bubble/BubbleEventHandler.h"
#include "BubbleBobble/States/Bubble/BubbleSpawnState.h"
#include "BubbleBobble/States/Bubble/BubbleIdleState.h"
#include "BubbleBobble/States/Bubble/BubblePopState.h"
#include "BubbleBobble/States/Bubble/BubbleShotState.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "BubbleBobble/States/StateComponent.h"

#include "Scene.h"
#include "SceneManager.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "GameObject.h"
#include "BaseComponent.h"

dae::BubbleComponent::BubbleComponent(GameObject* owner, const std::string& spriteSheet, PlayerComponent* playerComponent)
	: BaseComponent(owner),
	m_spriteSheet{ spriteSheet }
{
	owner->SetLocalPosition(-100.0f, -100.0f, 0.0f);

	owner->AddComponent(std::make_unique<AnimationComponent>(owner, m_spriteSheet));
	owner->GetComponent<AnimationComponent>()->SetDestinationSize(glm::vec2{ static_cast<float>(m_dstSize) });

	int row{ 4 };
	int numFrames{ 3 };
	AnimationData spawnBubbleAnimation{ row, numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubbleSpawn", spawnBubbleAnimation);

	row = 5;
	numFrames = 1;
	AnimationData idleBubbleAnimation{ row, numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubbleIdle", idleBubbleAnimation);

	row = 6;
	numFrames = 2;
	AnimationData popBubbleAnimation{ row, numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubblePop", popBubbleAnimation);

	owner->AddComponent(std::make_unique<BubbleEventHandlerComponent>(owner));

	owner->AddComponent(std::make_unique<ColliderComponent>(owner, m_dstSize, ColliderType::Trigger));

	owner->GetComponent<ColliderComponent>()->AddObserver(owner->GetComponent<BubbleEventHandlerComponent>());

	auto stateComponent = std::make_unique<StateComponent>(owner);
	stateComponent->AddState("Idle", std::make_unique<BubbleIdleState>(owner));
	stateComponent->AddState("Pop", std::make_unique<BubblePopState>(owner));
	stateComponent->AddState("Shot", std::make_unique<BubbleShotState>(owner, playerComponent->GetGameObject(), this));
	stateComponent->AddState("Spawn", std::make_unique<BubbleSpawnState>(owner));

	owner->AddComponent(std::move(stateComponent));
}