#include "ZenChanComponent.h"

#include <memory>

#include "AnimationComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "BubbleBobble/States/StateComponent.h"
#include "BubbleBobble/States/ZenChan/ZenChanChaseState.h"
#include "BubbleBobble/States/ZenChan/ZenChanSpawnState.h"
#include "BubbleBobble/States/ZenChan/ZenChanVulnerableState.h"

namespace dae
{
	ZenChanComponent::ZenChanComponent(GameObject* owner, glm::vec3& direction, ColliderType type)
		: BaseComponent(owner)
	{
		auto animComp = std::make_unique<AnimationComponent>(owner, std::string{ m_spriteSheetPath });
		animComp->SetDestinationSize(glm::vec2{ static_cast<float>(m_dstSize) });
		animComp->SetForwardDirection(direction);

		animComp->AddAnimation("Walk", AnimationData{ 0, 2 });
		animComp->AddAnimation("AngryWalk", AnimationData{ 1, 2 });
		animComp->AddAnimation("Bubble", AnimationData{ 3, 2, 16, 0.25f });
		animComp->AddAnimation("AngryBubble", AnimationData{ 5, 2, 16, 0.25f });

		owner->AddComponent(std::move(animComp));

		owner->AddComponent(std::make_unique<ColliderComponent>(owner, m_dstSize, type));
		owner->AddComponent(std::make_unique<RigidBodyComponent>(owner));

		auto stateComp = std::make_unique<StateComponent>(owner);
		stateComp->AddState("Spawn", std::make_unique<ZenChanSpawnState>(owner));
		stateComp->AddState("Chase", std::make_unique<ZenChanChaseState>(owner));
		stateComp->AddState("Vulnerable", std::make_unique<ZenChanVulnerableState>(owner));
		stateComp->SetState("Spawn");

		owner->AddComponent(std::move(stateComp));

		const auto pos = owner->GetLocalPosition().GetPosition();

		owner->SetLocalPosition(
			pos.x * static_cast<float>(m_srcSize),
			pos.y * static_cast<float>(m_srcSize),
			pos.z
		);
	}
}