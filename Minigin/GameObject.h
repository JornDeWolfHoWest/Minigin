#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <string>
namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:
		virtual void Update(const float& deltaTime);
		virtual void FixedUpdate();
		virtual void Render() const;

		void SetLocalPosition(glm::vec3 position);
		void UpdateWorldPosition();
		glm::vec3& GetLocalPosition();
		glm::vec3& GetWorldPosition();
		
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition);

		bool IsChild(GameObject* child) const;
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsComponent(BaseComponent* component) const;
		void AddComponent(BaseComponent* component);
		void RemoveComponent(BaseComponent* component);

		void CheckForDeleteableObjects();
		void DeleteObject();
		void MarkForDeletion();
		
		GameObject(std::shared_ptr<GameObject> parent);
		virtual ~GameObject();

	private:
		bool m_DirtyPosition{};
		bool m_MarkedForDeletion{};
		std::shared_ptr<GameObject> m_Parent{};
		std::vector<GameObject*> m_Children{};
		std::vector<BaseComponent*> m_Components{};
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
	};
}
