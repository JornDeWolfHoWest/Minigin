#include "HealthObserverComponent.h"
#include "GameObject.h"
#include "GameSettings.h"
#include "TextComponent.h"
#include <string>

namespace dae
{
	HealthObserverComponent::HealthObserverComponent(GameObject* owner) :
		BaseComponent(owner)
	{}

	void HealthObserverComponent::Update(const float& /*deltaTime*/)
	{
		// Lazily cache and update text display on first update
		if (!m_pTextComponent)
		{
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
			UpdateText();
		}
	}

	void HealthObserverComponent::OnHealthChanged(int newHealth, int playerNumber)
	{
		if (playerNumber == 1)
		{
			m_player1Health = newHealth;
		}
		else
		{
			m_player2Health = newHealth;
		}

		UpdateText();
	}

	void HealthObserverComponent::OnPlayerDied()
	{
		GameSettings::GetInstance().SetGameState(GameSettings::GameState::Gameover, -1);
	}

	void HealthObserverComponent::Init(int player1Health, int player2Health)
	{
		m_player1Health = player1Health;
		m_player2Health = player2Health;
		UpdateText();
	}

	void HealthObserverComponent::UpdateText()
	{
		if (!m_pTextComponent)
		{
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
		}

		if (m_pTextComponent)
		{
			// Setup for p2
			m_pTextComponent->SetText("     " + std::to_string(m_player1Health) + "                          " + std::to_string(m_player2Health));
		}
	}
}