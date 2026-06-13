#pragma once
#include <BaseComponent.h>

#include "Qbert.h"
#include <GameObject.h>


namespace game
{
	class GameOver : public dae::BaseComponent, public QbertObserver
	{
	public:
		GameOver(dae::GameObject* owner) : BaseComponent(owner) { GetOwner()->SetActive(false); }
		virtual ~GameOver() = default;

		void Update(const float&) override {};
		void FixedUpdate() override {};
		void Render() const override {};

		void QbertLives(int lives) override;
		void QbertRespawn() override {};
	};
}
