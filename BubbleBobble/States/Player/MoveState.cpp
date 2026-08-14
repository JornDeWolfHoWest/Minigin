#include "MoveState.h"
#include "AnimationComponent.h"
#include "FallState.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "BubbleBobble/RigidBodyComponent.h"
#include "BubbleBobble/States/StateComponent.h"
#include "GameObject.h"
#include <iostream>

dae::MoveState::MoveState(GameObject* owner, int playerNumber, PlayerComponent* playerComponent) :
	State(owner),
	m_playerNumber(playerNumber),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb(GetOwner()->GetComponent<RigidBodyComponent>()),
	m_playerComponent(playerComponent)
{}

dae::MoveState::~MoveState() = default;

void dae::MoveState::OnEnter()
{
	if (m_animationComponent)
	{
		m_animationComponent->SetCurrentAnimation("Walk");
	}

	if (auto eventHandler = GetOwner()->GetComponent<PlayerEventHandlerComponent>())
	{
		eventHandler->OnPlayerMove(GetOwner());
	}
}

void dae::MoveState::OnExit()
{}

void dae::MoveState::Update(const float& /*deltaTime*/)
{
	if (!m_rb) return;

	if (m_rb->GetVerticalVelocity() > 0.01f)
	{
		std::unique_ptr<State> fallState = std::make_unique<FallState>(GetOwner(), m_playerNumber);
		GetOwner()->GetComponent<StateComponent>()->SetState("Fall");
	}


	if (m_playerComponent)
	{
		if (!m_playerComponent->IsMovingHorizontally())
		{
			GetOwner()->GetComponent<StateComponent>()->SetState("Idle");
		}
	}
}