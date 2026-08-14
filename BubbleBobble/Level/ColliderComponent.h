#pragma once
#include "BaseComponent.h"
#include <Physics2DUtils.h>
#include <vector>

namespace dae
{
	class GameObject;
	class ColliderComponent;

	class CollisionObserver
	{
	public:
		virtual ~CollisionObserver() = default;
		virtual void OnCollision(ColliderComponent* self, ColliderComponent* other) = 0;
	};

	class ColliderComponent final : public BaseComponent
	{
	public:
		explicit ColliderComponent(GameObject* owner, int size, ColliderType type);
		virtual ~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {}
		void Render() const override;

		void DefineColliderRays(float offset);
		void PerformCollisionTests();

		bool IsColliding(const Collider& other) const;

		bool IsCollidingBottom() const { return m_isCollidingBottom; }
		bool IsCollidingTop() const { return m_isCollidingTop; }
		bool IsCollidingLeft() const { return m_isCollidingLeft; }
		bool IsCollidingRight() const { return m_isCollidingRight; }

		bool IsCollidingAllBottom() const { return m_isCollidingAllBottom; }
		bool IsCollidingAllTop() const { return m_isCollidingAllTop; }
		bool IsCollidingAllLeft() const { return m_isCollidingAllLeft; }
		bool IsCollidingAllRight() const { return m_isCollidingAllRight; }

		void StartJumping() { m_isInAir = true; }
		void Land() { m_isInAir = false; }

		void AddObserver(CollisionObserver* observer);
		void RemoveObserver(CollisionObserver* observer);

		GameObject* GetGameObject() const { return GetOwner(); }

	private:
		void Init();
		void ResolveCollision(ColliderComponent* other);
		void DispatchCollisionEvents(ColliderComponent* other);

		Collider m_collider{};
		ColliderType m_type{};

		std::vector<CollisionObserver*> m_pObservers{};
		static std::vector<ColliderComponent*> m_colliderComponents;

		bool m_isInAir{ true };

		bool m_isCollidingBottom{ false };
		bool m_isCollidingTop{ false };
		bool m_isCollidingLeft{ false };
		bool m_isCollidingRight{ false };

		bool m_isCollidingAllBottom{ false };
		bool m_isCollidingAllTop{ false };
		bool m_isCollidingAllLeft{ false };
		bool m_isCollidingAllRight{ false };

		Ray m_bottomLeft{};
		Ray m_bottomRight{};
		Ray m_topLeft{};
		Ray m_topRight{};
		Ray m_leftBottom{};
		Ray m_leftTop{};
		Ray m_rightBottom{};
		Ray m_rightTop{};
	};
}