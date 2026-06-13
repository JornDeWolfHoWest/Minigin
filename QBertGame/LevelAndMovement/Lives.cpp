#include "Lives.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <stdexcept>

game::Lives::Lives(dae::GameObject* owner, int lives) :
	dae::BaseComponent(owner),
	m_Lives(lives)
{
	m_TextComponent = GetOwner()->GetComponent<dae::TextComponent>();
	if (m_TextComponent == nullptr)
	{
		throw std::runtime_error("Lives requires a TextComponent.");
	}
	SetText();

}

void game::Lives::QbertLives(int lives)
{
	m_Lives = lives;
	SetText();
}

void game::Lives::QbertRespawn()
{}

void game::Lives::SetText()
{
	m_TextComponent->SetText(std::to_string(m_Lives));
}
