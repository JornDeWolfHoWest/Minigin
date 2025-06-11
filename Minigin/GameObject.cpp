#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto iterator = std::find(m_Children.begin(), m_Children.end(), child);
	m_Children.erase(iterator);
}

bool dae::GameObject::IsComponent(BaseComponent* component) const
{
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		if (m_Components[index] == component)
			return true;
	}
	return false;
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_Components.push_back(component);
}

void dae::GameObject::RemoveComponent(BaseComponent* component)
{
	auto iterator = std::find(m_Components.begin(), m_Components.end(), component);
	m_Components.erase(iterator);
}

void dae::GameObject::CheckForDeleteableObjects()
{
	if (m_MarkedForDeletion)
		this->DeleteObject();
	else
	{
		for (int index = 0; index < int(m_Children.size()); index++)
		{
			m_Children[index]->CheckForDeleteableObjects();
		}
	}
}

void dae::GameObject::DeleteObject()
{
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		delete m_Components[index];
	}
	delete this;
}

void dae::GameObject::MarkForDeletion()
{
	m_MarkedForDeletion = true;
}

dae::GameObject::GameObject(GameObject* parent)
{
	SetParent(parent, false);
}

dae::GameObject::~GameObject() {
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		if (m_Components[index] != nullptr)
			delete m_Components[index];
	}
}

void dae::GameObject::Update(const float& deltaTime)
{
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		m_Components[index]->Update(deltaTime);
	}
	for (int index = 0; index < int(m_Children.size()); index++)
	{
		m_Children[index]->Update(deltaTime);
	}
	UpdateWorldPosition();
}

void dae::GameObject::FixedUpdate()
{
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		m_Components[index]->FixedUpdate();
	}
	for (int index = 0; index < int(m_Children.size()); index++)
	{
		m_Children[index]->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	
	for (int index = 0; index < int(m_Components.size()); index++)
	{
		m_Components[index]->Render();
	}
	for (int index = 0; index < int(m_Children.size()); index++)
	{
		m_Children[index]->Render();
	}
}


void dae::GameObject::SetLocalPosition(glm::vec3 position)
{
	m_DirtyPosition = true;
	m_LocalPosition = position;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_DirtyPosition)
	{
		if (m_Parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
	}
	m_DirtyPosition = false;
}

glm::vec3& dae::GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_DirtyPosition)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		m_DirtyPosition = true;
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);

}

bool dae::GameObject::IsChild(GameObject* child) const
{
	for (int index = 0; index < int(m_Children.size()); index++)
	{
		if (m_Children[index] == child)
			return true;
	}
	return false;
}
