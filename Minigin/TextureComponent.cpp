#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::TextureComponent::TextureComponent(dae::GameObject* parent, const std::string& filename)
	: BaseComponent(parent),
	m_SrcX(0), m_SrcY(0), m_SrcWidth(-1), m_SrcHeight(-1), m_DrawHeight(0), m_DrawWidth(0)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void dae::TextureComponent::SetDrawSize(const float width, const float height)
{
	m_DrawWidth = width;
	m_DrawHeight = height;
}
void dae::TextureComponent::SetSrcRect(const float x, const float y, const float width, const float height)
{
	m_SrcX = x;
	m_SrcY = y;
	m_SrcWidth = width;
	m_SrcHeight = height;
}

void dae::TextureComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_DrawWidth, m_DrawHeight, m_SrcX, m_SrcY, m_SrcWidth, m_SrcHeight);
}

