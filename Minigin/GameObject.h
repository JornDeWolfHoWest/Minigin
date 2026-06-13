#pragma once
#include <string>
#include <memory>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;
	class GameObject 
	{
	public:
		virtual void Update(const float& deltaTime);
		virtual void FixedUpdate();
		virtual void Render();

		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(Transform position);
		void UpdateWorldPosition();
		Transform GetLocalPosition();
		Transform GetWorldPosition();
		void SetPositionDirty();

		void SetWorldScale(float x, float y);
		glm::vec2 GetWorldScale() const;

		void MarkForDeletion();
		void CheckForDeletion();
		bool IsMarkedForDeletion() { return m_MarkedForDeletion; }

		void SetActive(bool active) { m_IsActive = active; }
		bool IsActive() { return m_IsActive; }

		GameObject* GetParent() const { return m_pParent; }
		bool IsChild(const std::unique_ptr<GameObject>& pChild) const;
		void AddChild(std::unique_ptr<GameObject> pChild);
		std::unique_ptr<GameObject> DetachChild(GameObject* pChild);
		bool IsComponent(const std::unique_ptr<BaseComponent>& pComponent) const;
		void AddComponent(std::unique_ptr<BaseComponent> pComponent);
		void RemoveComponent(std::unique_ptr<BaseComponent>& pComponent);

		template<typename Component>
		Component* GetComponent();
		template<typename Component>
		std::vector<Component*> GetComponents(bool searchChildren = true);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	protected:
		GameObject* m_pParent{};
		bool m_DirtyPosition{};
		bool m_MarkedForDeletion{};
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};


		Transform m_WorldPosition{};
		Transform m_LocalPosition{};
		glm::vec2 m_WorldScale{};

		bool m_IsActive{ true };
	};


	template<typename Component>
	inline Component* GameObject::GetComponent()
	{
		for (const auto& component : m_pComponents)
		{
			if (auto castedComponent = dynamic_cast<Component*>(component.get()))
			{
				return castedComponent;
			}
		}
		return nullptr;
	}

	template<typename Component>
	inline std::vector<Component*> GameObject::GetComponents(bool searchChildren)
	{
		std::vector<Component*> components = std::vector<Component*>();
		for (const auto& component : m_pComponents)
		{
			if (auto castedComponent = dynamic_cast<Component*>(component.get()))
			{
				components.push_back(castedComponent);
			}
		}
		return components;
	}
}
