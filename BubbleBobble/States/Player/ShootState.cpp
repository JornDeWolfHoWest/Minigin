#include "ShootState.h"
#include "BubbleBobble/AnimationComponent.h"
#include "IdleState.h"
#include "BubbleBobble/SoundEffectsEnum.h"
#include <Services/SoundService.h>
#include "BubbleBobble/PlayerComponents/ShootBubbleComponent.h"
#include "GameObject.h"


dae::ShootState::ShootState(GameObject* owner, int playerNumber) : State(owner), m_playerNumber(playerNumber)
{}

dae::ShootState::~ShootState()
{}

void dae::ShootState::OnEnter()
{
	GetOwner()->GetComponent<ShootBubbleComponent>()->Shoot();
	// dae::SoundLocator::GetAudio().Play(static_cast<SoundId>(SoundEffectsEnum::ShootBullet), 1.0f);
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Shoot");
	}
}

void dae::ShootState::OnExit()
{}

void dae::ShootState::Update(const float& deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_hitDuration)
	{
		GetOwner()->GetComponent<StateComponent>()->SetState("Idle");
		m_timer = 0;
	}
}