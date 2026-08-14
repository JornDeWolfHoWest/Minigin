#include "ScoreComponent.h"
#include "GameObject.h"
#include <algorithm>

namespace dae
{
	ScoreComponent::ScoreComponent(GameObject* owner, int score, int playerNumber)
		: BaseComponent(owner)
		, m_currentScore(score)
		, m_playerNumber(playerNumber)
	{}

	void ScoreComponent::Update(const float& /*deltaTime*/)
	{}

	void ScoreComponent::FixedUpdate()
	{}

	void ScoreComponent::Render() const
	{}

	void ScoreComponent::SetScore(int score)
	{
		m_currentScore = score;
		NotifyObservers([this](ScoreObserver* observer) {
			observer->OnScoreChanged(m_currentScore, m_playerNumber);
			});
	}

	void ScoreComponent::AddToScore(int scoreToAdd)
	{
		m_currentScore += scoreToAdd;
		NotifyObservers([this](ScoreObserver* observer) {
			observer->OnScoreChanged(m_currentScore, m_playerNumber);
			});
	}

	int ScoreComponent::GetScore() const
	{
		return m_currentScore;
	}

	void ScoreComponent::AddObserver(ScoreObserver* observer)
	{
		if (observer && std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
		{
			m_observers.push_back(observer);
		}
	}

	void ScoreComponent::RemoveObserver(ScoreObserver* observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

	void ScoreComponent::NotifyObservers(std::function<void(ScoreObserver*)> observerFunction)
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