#include "JumpState.h"
#include "AnimationComponent.h"
#include "FallState.h"
#include "IdleState.h"
#include "InputManager.h"
#include "MoveState.h"
#include "RigidBodyComponent.h"
#include <iostream>
#include "GameObject.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "BubbleBobble/States/StateComponent.h"

dae::JumpState::JumpState(GameObject* owner, int playerNumber) :
	State(owner),
	m_playerNumber(playerNumber),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb{ GetOwner()->GetComponent<RigidBodyComponent>() }
{}

dae::JumpState::~JumpState()
{}

void dae::JumpState::OnEnter()
{
	m_animationComponent->SetCurrentAnimation("JumpUp");
	m_rb->Jump();
}

void dae::JumpState::OnExit()
{}

void dae::JumpState::Update(const float&)
{
	if (GetOwner()->GetComponent<RigidBodyComponent>()->GetVerticalVelocity() < 0)
	{
		GetOwner()->GetComponent<ColliderComponent>()->StartJumping();
	}
	else
	{
		GetOwner()->GetComponent<ColliderComponent>()->Land();
		GetOwner()->GetComponent<StateComponent>()->SetState("Fall");
	}
}