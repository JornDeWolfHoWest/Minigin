#include "HitState.h"
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "BubbleBobble/States/Player/SpawnState.h"
#include "GameObject.h"

dae::HitState::HitState(GameObject* owner, int playerNumber) : State(owner), m_playerNumber(playerNumber)
{}

dae::HitState::~HitState()
{}

void dae::HitState::OnEnter()
{
	GetOwner()->GetComponent<ColliderComponent>()->SetActive(false);
	GetOwner()->GetComponent<RigidBodyComponent>()->SetActive(false);

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Death");
	}
}

void dae::HitState::OnExit()
{}

void dae::HitState::Update(const float& deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_hitDuration)
	{
		auto pos = GetOwner()->GetComponent<PlayerComponent>()->GetSpawnPosition();
		auto dir = GetOwner()->GetComponent<PlayerComponent>()->GetSpawnDirection();

		m_timer = 0;
		GetOwner()->GetComponent<StateComponent>()->SetState("Spawn");
	}
}