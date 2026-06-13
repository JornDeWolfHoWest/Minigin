#include "Score.h"
#include "GameObject.h"
#include <TextComponent.h>

game::Score::Score(dae::GameObject* owner, std::shared_ptr<dae::Font> font) :
	BaseComponent(owner),
	m_Score(0)
{
	GetOwner()->AddComponent(std::make_unique<dae::TextComponent>(GetOwner(), font, ""));
	m_TextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}


void game::Score::AddScore(int score)
{
	m_Score += score;
	if (m_TextComponent)
	{
		m_TextComponent->SetText(std::to_string(m_Score));
	}
}
