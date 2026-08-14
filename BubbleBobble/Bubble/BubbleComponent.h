#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class PlayerComponent;

	class BubbleComponent final : public BaseComponent
	{
	public:
		BubbleComponent(GameObject* owner, const std::string& spriteSheet, PlayerComponent* playerComponent);
		virtual ~BubbleComponent() override = default;

		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

		bool IsAvailable() const { return m_isAvailable; }
		void SetIsAvailable(bool available) { m_isAvailable = available; }
		float GetSpeed() const { return m_speed; }
		int GetMoveDistance() const { return m_moveDistance; }

	private:
		bool m_isAvailable{ true };
		int m_srcSize{ 16 };
		int m_dstSize{ 32 };
		float m_speed{ 128.0f };
		int m_moveDistance{ 160 };
		std::string m_spriteSheet{};
	};
}