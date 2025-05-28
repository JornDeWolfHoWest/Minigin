#include "HealthDisplay.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <iomanip>
#include "BaseComponent.h"
#include "TextComponent.h"
#include "HealthChangedEvent.h"

namespace dae {
	void HealthDisplayComponent::Update(const float& deltaTime)
	{
		m_TextComponent->Update(deltaTime);
	}

	void HealthDisplayComponent::Render() const
	{
		m_TextComponent->Render();
	}

	void HealthDisplayComponent::Update(const Event& event)
	{
		if (event.GetType() == EventType::HealthChanged)
		{
			const HealthChangedEvent& healthEvent = static_cast<const HealthChangedEvent&>(event);
			std::cout << "Player health: " << healthEvent.GetHealth() << std::endl;


			std::string lives = "Lives: " + std::to_string(healthEvent.GetHealth()) ;

			m_TextComponent->SetText(lives);
			m_TextComponent->Update(0.f);
		}
	}

	void HealthDisplayComponent::SetPosition(float x, float y)
	{
		m_TextComponent->SetPosition(x, y);
	}

	HealthDisplayComponent::HealthDisplayComponent(std::shared_ptr<Font> font, GameObject* pOwner) :
		BaseComponent(pOwner),
		m_TextComponent(new TextComponent{ "0", font, pOwner })
	{
	}

	HealthDisplayComponent::~HealthDisplayComponent()
	{
	}
}