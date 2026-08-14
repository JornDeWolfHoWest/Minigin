#include "IdleState.h"
#include "AnimationComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "GameObject.h"
#include "BubbleBobble/States/StateComponent.h"
#include "MoveState.h"
#include "InputManager.h"
#include <SDL3/SDL_keycode.h>

dae::IdleState::IdleState(GameObject* owner, int playerNumber, PlayerComponent* playerComponent)
	: State(owner),
	m_playerNumber(playerNumber),
	m_playerComponent(playerComponent)
{}

dae::IdleState::~IdleState() = default;

void dae::IdleState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Idle");
	}

	if (auto eventHandler = GetOwner()->GetComponent<PlayerEventHandlerComponent>())
	{
		eventHandler->OnPlayerIdle();
	}
}

void dae::IdleState::OnExit()
{
}

void dae::IdleState::Update(const float& /*deltaTime*/)
{
	if (m_playerComponent)
	{
		if (m_playerComponent->IsMovingHorizontally())
		{
			GetOwner()->GetComponent<StateComponent>()->SetState("Move");
		}
	}
}