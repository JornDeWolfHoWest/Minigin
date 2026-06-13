#include <string>
#include <algorithm>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Transform.h"

using namespace dae;

GameObject::GameObject()
	: m_pParent(nullptr)
	, m_DirtyPosition(false)
	, m_MarkedForDeletion(false)
	, m_pChildren()
	, m_pComponents()
	, m_WorldPosition()
	, m_LocalPosition()
	, m_WorldScale{-1,-1}
{
}

GameObject::~GameObject()
{
	// children are stored as unique_ptr, they will be destroyed automatically
}

void GameObject::Update(const float& deltaTime)
{
	if (!m_IsActive)
	{
		return;
	}
	for (const auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
	for (const auto& child : m_pChildren)
	{
		if (child)
			child->Update(deltaTime);
	}
}

void GameObject::FixedUpdate()
{
	if (!m_IsActive)
	{
		return;
	}
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
	if (!m_IsActive)
	{
		return;
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

void GameObject::SetWorldScale(float x, float y)
{
	m_WorldScale = { x, y };
}


glm::vec2 GameObject::GetWorldScale() const
{
	return m_WorldScale;
}


void dae::GameObject::SetPositionDirty()
{
	m_DirtyPosition = true;
	for (auto &child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::MarkForDeletion()
{
	m_MarkedForDeletion = true;
	for (auto &child : m_pChildren)
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
	for (auto &child : m_pChildren)
	{
		child->CheckForDeletion();
	}
}

bool dae::GameObject::IsChild(const std::unique_ptr<GameObject>& pChild) const
{
	return std::find(m_pChildren.begin(), m_pChildren.end(), pChild) != m_pChildren.end();
}

std::unique_ptr<GameObject> GameObject::DetachChild(GameObject* pChild)
{
	auto it = std::find_if(
		m_pChildren.begin(),
		m_pChildren.end(),
		[pChild](const std::unique_ptr<GameObject>& child)
		{
			return child.get() == pChild;
		});

	if (it == m_pChildren.end())
	{
		return nullptr;
	}

	(*it)->m_pParent = nullptr;

	std::unique_ptr<GameObject> detached = std::move(*it);
	m_pChildren.erase(it);

	return detached;
}

void dae::GameObject::AddChild(std::unique_ptr<GameObject> pChild)
{
	if (!pChild)
		return;
	pChild->m_pParent = this;
	m_pChildren.push_back(std::move(pChild));
}

bool dae::GameObject::IsComponent( const std::unique_ptr<BaseComponent>& pComponent) const
{
	return std::find(m_pComponents.begin(), m_pComponents.end(), pComponent) != m_pComponents.end();
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> pComponent)
{
	m_pComponents.push_back(std::move(pComponent));
}

void dae::GameObject::RemoveComponent(std::unique_ptr<BaseComponent>&	 pComponent)
{
	auto iterator = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
	m_pComponents.erase(iterator);
}
