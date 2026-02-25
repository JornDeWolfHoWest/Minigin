#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Transform.h"

using namespace dae;

GameObject::~GameObject() {
	this;
	for (int index = 0; index < m_pComponents.size(); index++)
	{
		delete m_pComponents[index];
	}
	for (int index = 0; index < m_pChildren.size(); index++)
	{
		delete m_pChildren[index];
	}
}

void GameObject::Update(const float& deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
	for (const auto& child : m_pChildren)
	{
		child->Update(deltaTime);
	}
}

void GameObject::FixedUpdate()
{
	for (int index = 0; index < m_pComponents.size(); index++)
	{
		m_pComponents[index]->FixedUpdate();
	}
	for (int index = 0; index < m_pChildren.size(); index++)
	{
		m_pChildren[index]->FixedUpdate();
	}
}

void GameObject::Render() const
{
	const auto& pos = GetWorldPosition();
	if (m_texture)
		Renderer::GetInstance().RenderTexture(*m_texture, pos.GetPosition().x, pos.GetPosition().y);
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}

void GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void GameObject::SetLocalPosition(float x, float y, float z)
{
	Transform transform;
	transform.SetPosition(x, y, z);
	SetLocalPosition(transform);
}

void GameObject::SetLocalPosition(Transform position)
{
	m_DirtyPosition = true;
	m_LocalPosition = position;
	UpdateWorldPosition();
}

void GameObject::UpdateWorldPosition()
{
	if (m_DirtyPosition)
	{
		if (m_pParent)
		{
			m_WorldPosition.SetPosition(m_pParent->GetWorldPosition().GetPosition() + m_LocalPosition.GetPosition());
		}
		else
		{
			m_WorldPosition = m_LocalPosition;
		}
		m_DirtyPosition = false;
	}
}

Transform GameObject::GetLocalPosition() const
{
	return m_LocalPosition;
}

Transform GameObject::GetWorldPosition() const
{
	return m_WorldPosition;
}

void dae::GameObject::MarkForDeletion()
{
	m_MarkedForDeletion = true;
	for (auto child : m_pChildren)
	{
		child->m_MarkedForDeletion = true;
	}
}

bool dae::GameObject::IsChild(const GameObject* pChild) const
{
	return std::find(m_pChildren.begin(), m_pChildren.end(), pChild) != m_pChildren.end();
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

bool dae::GameObject::IsComponent(BaseComponent* pComponent) const
{
	return std::find(m_pComponents.begin(), m_pComponents.end(), pComponent) != m_pComponents.end();
}

void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	m_pComponents.push_back(pComponent);
}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	auto iterator = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
	m_pComponents.erase(iterator);
}
