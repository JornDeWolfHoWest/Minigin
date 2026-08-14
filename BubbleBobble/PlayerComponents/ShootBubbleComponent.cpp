#include "ShootBubbleComponent.h"
#include "GameObject.h"
#include "BubbleBobble/Bubble/BubbleComponent.h"
#include "BubbleBobble/States/Bubble/BubbleShotState.h"
#include "BubbleBobble/States/Bubble/BubblePopState.h"
#include "BubbleBobble/States/Bubble/BubbleSpawnState.h"
#include "BubbleBobble/States/Bubble/BubbleIdleState.h"
#include "BubbleBobble/States/StateComponent.h"
#include <algorithm>

dae::ShootBubbleComponent::ShootBubbleComponent(GameObject* owner, std::vector<GameObject*>& bubbles) :
	BaseComponent(owner),
	m_bubbles{ bubbles }
{}

void dae::ShootBubbleComponent::Update(const float&)
{}

void dae::ShootBubbleComponent::FixedUpdate()
{}

void dae::ShootBubbleComponent::Render() const
{}

void dae::ShootBubbleComponent::Shoot() const
{
	const auto iterator = std::ranges::find_if(m_bubbles, [](GameObject* bubble) {
		return bubble && bubble->GetComponent<BubbleComponent>() && bubble->GetComponent<BubbleComponent>()->IsAvailable();
		});

	if (iterator != m_bubbles.end())
	{
		auto stateComponent = (*iterator)->GetComponent<StateComponent>();
		
		stateComponent->SetState("Shot");
	}
}