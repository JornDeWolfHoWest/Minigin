#pragma once
#include "BaseComponent.h"
#include <functional>
#include <vector>

namespace dae
{
	class GameObject;
	class HealthObserver;

	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent(GameObject* owner, int maxHealth, int playerNumber = 1);
		virtual ~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		void SetCurrentHealth(int health);
		int GetCurrentHealth() const;

		void SetMaxHealth(int maxHealth);
		int GetMaxHealth() const;

		void SetPlayerNumber(int playerNumber) { m_playerNumber = playerNumber; }
		int GetPlayerNumber() const { return m_playerNumber; }

		void Damage(int damage);
		void Heal(int healing);

		void AddObserver(HealthObserver* observer);
		void RemoveObserver(HealthObserver* observer);

	private:
		void NotifyObservers(std::function<void(HealthObserver*)> observerFunction);

		int m_maxHealth{};
		int m_currentHealth{};
		int m_playerNumber{ 1 };
		std::vector<HealthObserver*> m_observers{};
	};
}