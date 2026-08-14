#pragma once

#include "BubbleBobble/States/StateComponent.h"
#include "Transform.h"
#include <glm/glm.hpp>

namespace dae
{
	class BubbleComponent;

	class BubbleShotState final : public State
	{
	public:
		BubbleShotState(GameObject* owner, GameObject* playerObject, BubbleComponent* bubbleComponent);
		~BubbleShotState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;

	private:
		GameObject* m_playerObject{ nullptr };
		BubbleComponent* m_bubbleComponent{ nullptr };

		glm::vec3 m_initialPlayerPos{};
		glm::vec3 m_playerForward{};

		float m_bubbleLifetimeTimer{ 0.0f };
		float m_maxBubbleLifetime{ 5.0f };
	};
}