#include "ScoreDisplayComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <iomanip>
#include "BaseComponent.h"
#include "TextComponent.h"
#include "ScoreChangedEvent.h"
#include <steam_api.h>

namespace dae {
	void ScoreDisplayComponent::Update(const float& deltaTime)
	{
		if(m_Score != m_PreviousScore)
		{
			m_PreviousScore = m_Score;
			std::cout << "Player score: " << m_Score << std::endl;


			std::string score = std::to_string(m_Score);

			m_TextComponent->SetText(score);
		}
		m_TextComponent->Update(deltaTime);
	}

	void ScoreDisplayComponent::Render() const
	{
		m_TextComponent->Render();
	}

	void ScoreDisplayComponent::SetPosition(float x, float y)
	{
		m_TextComponent->SetPosition(x, y);
	}
	
	ScoreDisplayComponent::ScoreDisplayComponent(std::shared_ptr<Font> font, GameObject* pOwner, int& score) :
		BaseComponent(pOwner),
		m_TextComponent(new TextComponent{ "Score: ", font, pOwner }),
		m_Score(score)
	{
	}

	ScoreDisplayComponent::~ScoreDisplayComponent()
	{
	}
}