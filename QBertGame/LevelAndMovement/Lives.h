#pragma once
#include <BaseComponent.h>

#include "Qbert.h"

namespace dae
{
	class TextComponent;
	class GameObject;
}

namespace game
{
	class Lives : public dae::BaseComponent, public QbertObserver
	{
	public:
		Lives(dae::GameObject* owner, int lives = 3);
		virtual ~Lives() = default;

		void Start();

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

		void QbertLives(int lives) override;
		void QbertRespawn() override;

	private:
		void SetText();

		dae::TextComponent* m_TextComponent;
		int m_Lives;
	};
}
