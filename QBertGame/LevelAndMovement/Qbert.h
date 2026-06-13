#pragma once
#include <BaseComponent.h>
#include <functional>
#include <vector>

#include "Level.h"
#include "MovementObserver.h"
#include "RenderComponent.h"
#include <GameObject.h>

namespace game
{
	class QbertObserver
	{
	public:
		QbertObserver() = default;
		virtual ~QbertObserver() = default;
		virtual void QbertLives(int lives) = 0;
		virtual void QbertRespawn() = 0;
	};

	class MovementSystem;

	class Qbert : public dae::BaseComponent, public MovementObserver, public LevelObserver, public QbertObserver
	{
	public:
		Qbert(dae::GameObject* owner, int lives = 3, float respawnTime = 2.0f);
		virtual ~Qbert() = default;
		void CheckForComponentsNeeded();

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {};
		void Render() const override {};

		void Damage();

		void Fall() override;

		void AddObserver(QbertObserver* observer);

		int GetLives() const { return m_Lives; }

		void LevelDisc() override;
		void NextLevel() override;
		void GameComplete() override;

		void QbertLives(int lives) override;
		void QbertRespawn() override;

	private:
		void NotifyObservers(std::function<void(QbertObserver*)> observerFunction);

		std::vector<QbertObserver*> m_QbertObservers;
		MovementSystem* m_Movement;
		dae::RenderComponent* m_RenderComponent;
		int m_Lives;
		float m_RespawnTimer;
		float m_RespawnTime;
		bool m_NotifyLife;
	};
}
