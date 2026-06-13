#pragma once
#include <BaseComponent.h>

#include "Level.h"
#include <GameObject.h>

namespace game
{
	class GameDone : public dae::BaseComponent, public LevelObserver
	{
	public:
		GameDone(dae::GameObject* owner) : BaseComponent(owner) { GetOwner()->SetActive(false); }
		virtual ~GameDone() = default;

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

		void LevelDisc() override;
		void NextLevel() override;
		void GameComplete() override;
	};
}
