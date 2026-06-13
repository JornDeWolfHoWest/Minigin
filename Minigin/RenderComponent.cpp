#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(GameObject* owner, const std::string& filename) : BaseComponent(owner)
{
	SetTexture(filename);
}

void dae::RenderComponent::Render() const
{
	if (!m_Texture)
	{
		return;
	}

	const auto gameObject = GetOwner();
	if (!gameObject)
	{
		return;
	}

	const auto& pos = gameObject->GetWorldPosition();
	const auto& scale = gameObject->GetWorldScale();
	if (scale.x < 0 || scale.y < 0)
	{
		Renderer::GetInstance().RenderTexture(
			*m_Texture,
			pos.GetPosition().x,
			pos.GetPosition().y
		);
		return;
	}

	Renderer::GetInstance().RenderTexture(
		*m_Texture,
		pos.GetPosition().x,
		pos.GetPosition().y,
		scale.x,
		scale.y
	);
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	if (filename.empty())
	{
		m_Texture.reset();
		return;
	}
	
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
