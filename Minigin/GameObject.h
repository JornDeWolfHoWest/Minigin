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
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(Transform position);
		void UpdateWorldPosition();
		Transform GetLocalPosition() const;
		Transform GetWorldPosition() const;

		void MarkForDeletion();


		bool IsChild(const GameObject* pChild) const;
		void AddChild(GameObject* pChild);
		bool IsComponent(BaseComponent* pComponent) const;
		void AddComponent(BaseComponent* pComponent);
		void RemoveComponent(BaseComponent* pComponent);

		GameObject(GameObject* parent) : m_pParent(parent) { if (parent) parent->AddChild(this); }
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	protected:
		bool m_DirtyPosition{};
		bool m_MarkedForDeletion{};
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};
		std::vector<BaseComponent*> m_pComponents{};


		Transform m_WorldPosition{};
		Transform m_LocalPosition{};

		std::shared_ptr<Texture2D> m_texture{};
	};
}
