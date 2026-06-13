#pragma once
#include <BaseComponent.h>
#include <TextComponent.h>

class dae::GameObject;

namespace game
{
	class Score : public dae::BaseComponent
	{
	public:
		Score(dae::GameObject* owner, std::shared_ptr<dae::Font> font);
		virtual ~Score() = default;


		void AddScore(int score);

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

	private:
		dae::TextComponent* m_TextComponent;
		unsigned int m_Score;
	};
}
