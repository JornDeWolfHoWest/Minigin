#pragma once
#include "BaseComponent.h"
#include <functional>
#include <vector>

namespace dae
{
	class GameObject;

	class ScoreObserver
	{
	public:
		ScoreObserver() = default;
		virtual ~ScoreObserver() = default;

		virtual void OnScoreChanged(int newScore, int playerNumber) = 0;
	};

	class ScoreComponent final : public BaseComponent
	{
	public:
		ScoreComponent(GameObject* owner, int score, int playerNumber = 1);
		virtual ~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		// BaseComponent overrides
		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		void SetScore(int score);
		void AddToScore(int scoreToAdd);
		int GetScore() const;

		void SetPlayerNumber(int playerNumber) { m_playerNumber = playerNumber; }
		int GetPlayerNumber() const { return m_playerNumber; }

		void AddObserver(ScoreObserver* observer);
		void RemoveObserver(ScoreObserver* observer);

	private:
		void NotifyObservers(std::function<void(ScoreObserver*)> observerFunction);

		int m_currentScore{};
		int m_playerNumber{ 1 };
		std::vector<ScoreObserver*> m_observers{};
	};
}