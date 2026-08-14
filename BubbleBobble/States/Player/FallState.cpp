#include "FallState.h"
#include "AnimationComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "BubbleBobble/PlayerComponents/PlayerComponent.h"
#include "IdleState.h"
#include "GameObject.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

dae::FallState::FallState(GameObject* owner, int playerNumber) : State(owner), m_playerNumber(playerNumber)
{}

dae::FallState::~FallState()
{}

void dae::FallState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("FallDown");
	}

	if (auto* eventHandler = GetOwner()->GetComponent<PlayerEventHandlerComponent>())
	{
		eventHandler->OnPlayerFall(GetOwner());
	}

	GetOwner()->GetComponent<ColliderComponent>()->Land();
}

void dae::FallState::OnExit()
{}

void dae::FallState::Update(const float&)
{
	if (GetOwner()->GetComponent<ColliderComponent>()->IsCollidingBottom())
	{
		// If moving horizontally, transition to MoveState, else transition to IdleState
		if (GetOwner()->GetComponent<PlayerComponent>()->IsMovingHorizontally())
			GetOwner()->GetComponent<StateComponent>()->SetState("Move");
		else
			GetOwner()->GetComponent<StateComponent>()->SetState("Idle");
		return;
	}

	int width{}, height{};
	SDL_GetCurrentRenderOutputSize(dae::Renderer::GetInstance().GetSDLRenderer(), &width, &height);

	if (GetOwner()->GetLocalPosition().GetPosition().y > height)
	{
		auto pos = GetOwner()->GetLocalPosition().GetPosition();
		GetOwner()->SetLocalPosition(pos.x, 0, pos.z);
	}
}