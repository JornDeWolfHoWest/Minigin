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
		m_TextComponent->Update(deltaTime);
	}

	void ScoreDisplayComponent::Render() const
	{
		m_TextComponent->Render();
	}

	void ScoreDisplayComponent::Update(const Event& event)
	{
		if (event.GetType() == EventType::ScoreChanged)
		{
			const ScoreChangedEvent& scoreEvent = static_cast<const ScoreChangedEvent&>(event);
			std::cout << "Player score: " << scoreEvent.GetScore() << std::endl;


			std::string score = "Score: " + std::to_string(scoreEvent.GetScore());

			m_TextComponent->SetText(score);
			m_TextComponent->Update(0.f);
		}
	}

	void ScoreDisplayComponent::SetPosition(float x, float y)
	{
		m_TextComponent->SetPosition(x, y);
	}

	ScoreDisplayComponent::ScoreDisplayComponent(std::shared_ptr<Font> font, GameObject* pOwner) :
		BaseComponent(pOwner),
		m_TextComponent(new TextComponent{ "Score: ", font, pOwner })
	{
	}

	ScoreDisplayComponent::~ScoreDisplayComponent()
	{
	}
}