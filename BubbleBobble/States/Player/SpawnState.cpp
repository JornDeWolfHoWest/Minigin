#include "SpawnState.h"

#include "BubbleBobble/Level/ColliderComponent.h"
#include "IdleState.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "BubbleBobble/States/StateComponent.h"
#include "GameObject.h"

dae::SpawnState::SpawnState(GameObject* owner, const glm::vec3& spawnPos, const glm::vec3& spawnDirection, int playerNumber) :
	State(owner),
	m_spawnPos{ spawnPos },
	m_spawnDir{ spawnDirection },
	m_playerNumber{ playerNumber }
{}

dae::SpawnState::~SpawnState()
{}

void dae::SpawnState::OnEnter()
{
	GetOwner()->SetLocalPosition(m_spawnPos.x, m_spawnPos.y, m_spawnPos.z);

	if (const auto collider = GetOwner()->GetComponent<ColliderComponent>())
	{
		collider->SetActive(true);
	}

	if (const auto rigidBody = GetOwner()->GetComponent<RigidBodyComponent>())
	{
		rigidBody->SetActive(true);
	}

	GetOwner()->GetComponent<StateComponent>()->SetState("Idle");
}

void dae::SpawnState::OnExit()
{
}

void dae::SpawnState::Update(const float& /*deltaTime*/)
{}