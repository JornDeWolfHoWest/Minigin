#include "Qbert.h"
#include <GameObject.h>
#include "MovementSystem.h"

game::Qbert::Qbert(dae::GameObject* owner, int lives, float respawnTime) :
	dae::BaseComponent(owner),
	m_Lives(lives),
	m_RespawnTimer(0),
	m_RespawnTime(respawnTime),
	m_NotifyLife(false), m_Movement(nullptr), m_RenderComponent(nullptr)
{}

void game::Qbert::CheckForComponentsNeeded()
{
	auto gameObject = GetOwner();
	m_Movement = gameObject->GetComponent<MovementSystem>();
	m_RenderComponent = gameObject->GetComponent<dae::RenderComponent>();
}

void game::Qbert::Update(const float& deltaTime)
{
	if (m_NotifyLife)
	{
		NotifyObservers([this](QbertObserver* observer) { observer->QbertLives(m_Lives); });
		m_NotifyLife = false;
	}
	if (m_Lives <= 0 || m_RespawnTimer <= 0)
	{
		return;
	}
	m_RespawnTimer -= deltaTime;
	if (m_RespawnTimer > 0)
	{
		return;
	}
	NotifyObservers(&QbertObserver::QbertRespawn);
	if (!m_Movement)
	{
		Damage();
		return;
	}
	m_Movement->CanMove(true);
	m_Movement->Respawn();
}

void game::Qbert::Damage()
{
	if (m_RespawnTimer > 0)
	{
		return;
	}
	--m_Lives;
	m_NotifyLife = true;
	m_RespawnTimer = m_RespawnTime;
	if (!m_Movement)
	{
		return;
	}
	m_Movement->CanMove(false);
}

void game::Qbert::Fall()
{
	Damage();
}

void game::Qbert::AddObserver(QbertObserver* observer)
{
	m_QbertObservers.push_back(observer);
}

void game::Qbert::LevelDisc()
{}

void game::Qbert::NextLevel()
{
	if (!m_Movement)
	{
		return;
	}
	m_Movement->Respawn(true);
}

void game::Qbert::GameComplete()
{
	if (!m_Movement)
	{
		return;
	}
	m_Movement->CanMove(false);
}

void game::Qbert::QbertLives(int lives)
{
	if (lives != 0 || !m_Movement)
	{
		return;
	}
	m_Movement->CanMove(false);
}

void game::Qbert::QbertRespawn()
{}

void game::Qbert::NotifyObservers(std::function<void(QbertObserver*)> observerFunction)
{
	for (auto* observer : m_QbertObservers)
	{
		if (observer)
		{
			observerFunction(observer);
		}
	}
}
