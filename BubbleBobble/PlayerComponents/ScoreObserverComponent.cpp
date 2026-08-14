#include "ScoreObserverComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <string>

namespace dae
{
	ScoreObserverComponent::ScoreObserverComponent(GameObject* owner) :
		BaseComponent(owner)
	{}

	void ScoreObserverComponent::Update(const float& /*deltaTime*/)
	{
		// Lazily fetch and initialize text display on first update if needed
		if (!m_pTextComponent)
		{
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
			UpdateText();
		}
	}

	void ScoreObserverComponent::OnScoreChanged(int newScore, int playerIndex)
	{
		if (playerIndex == 0)
		{
			m_player1Score = newScore;
		}
		else if (playerIndex == 1)
		{
			m_player2Score = newScore;
		}

		UpdateText();
	}

	void ScoreObserverComponent::Init(int player1Score, int player2Score)
	{
		m_player1Score = player1Score;
		m_player2Score = player2Score;
		UpdateText();
	}

	void ScoreObserverComponent::UpdateText()
	{
		if (!m_pTextComponent)
		{
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
		}

		if (m_pTextComponent)
		{
			std::string scoreString = "Score: " + std::to_string(m_player1Score);
			if (m_player2Score > 0)
			{
				scoreString += " | P2: " + std::to_string(m_player2Score);
			}
			m_pTextComponent->SetText(scoreString);
		}
	}
}