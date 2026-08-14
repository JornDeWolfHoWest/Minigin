#include "SpriteComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae
{
	SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilePath) :
		RenderComponent(owner, textureFilePath),
		m_sourceFrame{ 0, 0, m_Texture ? static_cast<int>(m_Texture->GetSize().x) : 0, m_Texture ? static_cast<int>(m_Texture->GetSize().y) : 0 },
		m_destWidth{ static_cast<float>(m_sourceFrame.w) },
		m_destHeight{ static_cast<float>(m_sourceFrame.h) },
		m_lastPosition{ GetOwner()->GetWorldPosition().GetPosition() }
	{}

	SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilePath, const glm::vec2& srcSize, int row, int col, const glm::vec2& destSize) :
		RenderComponent(owner, textureFilePath),
		m_sourceFrame{ col * static_cast<int>(srcSize.x), row * static_cast<int>(srcSize.y), static_cast<int>(srcSize.x), static_cast<int>(srcSize.y) },
		m_destWidth{ destSize.x },
		m_destHeight{ destSize.y },
		m_lastPosition{ GetOwner()->GetWorldPosition().GetPosition() }
	{}

	void SpriteComponent::Update(const float& /*deltaTime*/)
	{
		const auto currentPosition = GetOwner()->GetWorldPosition().GetPosition();

		float deltaX = currentPosition.x - m_lastPosition.x;

		if (deltaX > 0.0f)
		{
			m_flipMode = SDL_FLIP_NONE;
		}
		else if (deltaX < 0.0f)
		{
			m_flipMode = SDL_FLIP_HORIZONTAL;
		}

		m_lastPosition = currentPosition;
	}

	void SpriteComponent::Render() const
	{
		if (m_Texture)
		{
			const auto pos = GetOwner()->GetWorldPosition().GetPosition();

			Renderer::GetInstance().RenderTexture(
				*m_Texture,
				pos.x,
				pos.y,
				m_destWidth,
				m_destHeight,
				m_sourceFrame,
				m_flipMode);
		}
	}

	void SpriteComponent::SetSourceSize(const glm::ivec2& newSize)
	{
		m_sourceFrame.w = newSize.x;
		m_sourceFrame.h = newSize.y;
	}

	void SpriteComponent::SetSourcePosition(const glm::ivec2& newPos)
	{
		m_sourceFrame.x = newPos.x;
		m_sourceFrame.y = newPos.y;
	}

	void SpriteComponent::SetDestinationSize(const glm::vec2& newSize)
	{
		m_destWidth = newSize.x;
		m_destHeight = newSize.y;
	}
}