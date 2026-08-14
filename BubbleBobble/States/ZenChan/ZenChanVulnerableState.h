#pragma once

#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class AnimationComponent;

	class ZenChanVulnerableState final : public State
	{
	public:
		explicit ZenChanVulnerableState(GameObject* owner);
		~ZenChanVulnerableState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;

	private:
		AnimationComponent* m_animationComponent{ nullptr };
		float m_maxVulnerableTime{ 15.0f };
		float m_angryTime{ 10.0f };
		float m_respawnTimer{ 0.0f };
	};
}