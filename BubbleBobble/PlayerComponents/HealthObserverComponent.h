#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class HealthObserver
	{
	public:
		virtual ~HealthObserver() = default;
		virtual void OnHealthChanged(int newHealth, int playerNumber) = 0;
		virtual void OnPlayerDied() = 0;
	};

	class HealthObserverComponent final : public BaseComponent, public HealthObserver
	{
	public:
		explicit HealthObserverComponent(GameObject* owner);
		virtual ~HealthObserverComponent() override = default;

		HealthObserverComponent(const HealthObserverComponent& other) = delete;
		HealthObserverComponent(HealthObserverComponent&& other) = delete;
		HealthObserverComponent& operator=(const HealthObserverComponent& other) = delete;
		HealthObserverComponent& operator=(HealthObserverComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {}
		void Render() const override {}

		// HealthObserver Interface Implementation
		void OnHealthChanged(int newHealth, int playerNumber) override;
		void OnPlayerDied() override;

		void Init(int player1Health, int player2Health);

	private:
		void UpdateText();

		TextComponent* m_pTextComponent{ nullptr };
		int m_player1Health{ 3 };
		int m_player2Health{ 3 };
	};
}