#include "HealthComponent.h"
#include "GameObject.h"
#include "HealthObserverComponent.h"
#include <algorithm>

namespace dae
{
	HealthComponent::HealthComponent(GameObject* owner, int maxHealth, int playerNumber)
		: BaseComponent(owner)
		, m_maxHealth(maxHealth)
		, m_currentHealth(maxHealth)
		, m_playerNumber(playerNumber)
	{}

	void HealthComponent::Update(const float&)
	{}

	void HealthComponent::FixedUpdate()
	{}

	void HealthComponent::Render() const
	{}

	void HealthComponent::SetCurrentHealth(int health)
	{
		m_currentHealth = health;
		NotifyObservers([this](HealthObserver* observer) {
			observer->OnHealthChanged(m_currentHealth, m_playerNumber);
			if (m_currentHealth <= 0)
			{
				observer->OnPlayerDied();
			}
			});
	}

	void HealthComponent::Damage(int damage)
	{
		m_currentHealth -= damage;

		if (m_currentHealth <= 0)
		{
			m_currentHealth = 0;
			NotifyObservers([this](HealthObserver* observer) {
				observer->OnHealthChanged(m_currentHealth, m_playerNumber);
				observer->OnPlayerDied();
				});
		}
		else
		{
			NotifyObservers([this](HealthObserver* observer) {
				observer->OnHealthChanged(m_currentHealth, m_playerNumber);
				});
		}
	}

	void HealthComponent::Heal(int healing)
	{
		m_currentHealth += healing;
		if (m_currentHealth > m_maxHealth)
		{
			m_currentHealth = m_maxHealth;
		}

		NotifyObservers([this](HealthObserver* observer) {
			observer->OnHealthChanged(m_currentHealth, m_playerNumber);
			});
	}

	int HealthComponent::GetCurrentHealth() const
	{
		return m_currentHealth;
	}

	void HealthComponent::SetMaxHealth(int maxHealth)
	{
		if (maxHealth > m_currentHealth)
		{
			m_maxHealth = maxHealth;
		}
		else
		{
			m_currentHealth = maxHealth;
			m_maxHealth = m_currentHealth;
		}
	}

	int HealthComponent::GetMaxHealth() const
	{
		return m_maxHealth;
	}

	void HealthComponent::AddObserver(HealthObserver* observer)
	{
		if (observer && std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
		{
			m_observers.push_back(observer);
		}
	}

	void HealthComponent::RemoveObserver(HealthObserver* observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

	void HealthComponent::NotifyObservers(std::function<void(HealthObserver*)> observerFunction)
	{
		for (auto* observer : m_observers)
		{
			if (observer)
			{
				observerFunction(observer);
			}
		}
	}
}