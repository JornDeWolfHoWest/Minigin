#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Transform.h"

using namespace dae;

GameObject::~GameObject() {
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

void GameObject::Render()
{
	if (m_texture)
	{
		const auto& pos = GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.GetPosition().x, pos.GetPosition().y);
	}
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
	SetPositionDirty();
	m_LocalPosition = position;
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
		SetPositionDirty();
	}
}

Transform GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

Transform GameObject::GetWorldPosition()
{
	if (m_DirtyPosition)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::GameObject::SetPositionDirty()
{
	m_DirtyPosition = true;
	for (auto child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::MarkForDeletion()
{
	m_MarkedForDeletion = true;
	for (auto child : m_pChildren)
	{
		child->m_MarkedForDeletion = true;
	}
}

void dae::GameObject::CheckForDeletion()
{
	if (m_MarkedForDeletion)
	{
		delete this;
		return;
	}
	for (auto child : m_pChildren)
	{
		child->CheckForDeletion();
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
