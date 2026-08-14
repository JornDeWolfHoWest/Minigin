#include "ColliderComponent.h"
#include <GameObject.h>
#include <algorithm>
#include <SDL3/SDL.h>
#include <Renderer.h>
#include <glm/glm.hpp>
#include "BubbleBobble/Enemy/ZenChanComponent.h"

namespace dae
{
	std::vector<ColliderComponent*> ColliderComponent::m_colliderComponents{};

	ColliderComponent::ColliderComponent(GameObject* owner, int size, ColliderType type) :
		BaseComponent(owner),
		m_type(type)
	{
		
		m_collider.size.x = static_cast<float>(size);
		m_collider.size.y = static_cast<float>(size);

		m_colliderComponents.push_back(this);

		if (owner)
		{
			const auto pos = owner->GetWorldPosition();
			m_collider.pos.x = pos.GetPosition().x;
			m_collider.pos.y = pos.GetPosition().y;
		}
	}

	ColliderComponent::~ColliderComponent()
	{
		std::erase(m_colliderComponents, this);
	}

	void ColliderComponent::AddObserver(CollisionObserver* observer)
	{
		if (observer)
		{
			m_pObservers.push_back(observer);
		}
	}

	void ColliderComponent::RemoveObserver(CollisionObserver* observer)
	{
		std::erase(m_pObservers, observer);
	}

	void ColliderComponent::Update(const float& /*deltaTime*/)
	{
		if (m_type == ColliderType::Wall || m_type == ColliderType::Platform)
			return;

		if (GetOwner())
		{
			const auto pos = GetOwner()->GetWorldPosition();
			m_collider.pos.x = pos.GetPosition().x;
			m_collider.pos.y = pos.GetPosition().y;
		}

		DefineColliderRays(2.0f);

		PerformCollisionTests();
	}

	void ColliderComponent::Render() const
	{
		if (IsActive()) // Temp code to block out the collider rendering for now
			return;

		SDL_FRect colliderRect{ m_collider.pos.x,m_collider.pos.y,m_collider.size.x,m_collider.size.y };
		SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
		SDL_RenderRect(dae::Renderer::GetInstance().GetSDLRenderer(), &colliderRect);

		if (!(m_type == ColliderType::Wall || m_type == ColliderType::Platform))
		{
			SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 0, 0, 255, 255);

			// Draw bottom rays
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_bottomLeft.origin.x, m_bottomLeft.origin.y,
				m_bottomLeft.origin.x + m_bottomLeft.direction.x * 10, m_bottomLeft.origin.y + m_bottomLeft.direction.y * 10);
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_bottomRight.origin.x, m_bottomRight.origin.y,
				m_bottomRight.origin.x + m_bottomRight.direction.x * 10, m_bottomRight.origin.y + m_bottomRight.direction.y * 10);

			// Draw top rays
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_topLeft.origin.x, m_topLeft.origin.y,
				m_topLeft.origin.x + m_topLeft.direction.x * 10, m_topLeft.origin.y + m_topLeft.direction.y * 10);
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_topRight.origin.x, m_topRight.origin.y,
				m_topRight.origin.x + m_topRight.direction.x * 10, m_topRight.origin.y + m_topRight.direction.y * 10);

			// Draw left rays
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_leftBottom.origin.x, m_leftBottom.origin.y,
				m_leftBottom.origin.x + m_leftBottom.direction.x * 10, m_leftBottom.origin.y + m_leftBottom.direction.y * 10);
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_leftTop.origin.x, m_leftTop.origin.y,
				m_leftTop.origin.x + m_leftTop.direction.x * 10, m_leftTop.origin.y + m_leftTop.direction.y * 10);

			// Draw right rays
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_rightBottom.origin.x, m_rightBottom.origin.y,
				m_rightBottom.origin.x + m_rightBottom.direction.x * 10, m_rightBottom.origin.y + m_rightBottom.direction.y * 10);
			SDL_RenderLine(dae::Renderer::GetInstance().GetSDLRenderer(),
				m_rightTop.origin.x, m_rightTop.origin.y,
				m_rightTop.origin.x + m_rightTop.direction.x * 10, m_rightTop.origin.y + m_rightTop.direction.y * 10);
		}
	}

	void dae::ColliderComponent::DefineColliderRays(float offset)
	{
		// Define rays for each side, closer to the center
		m_bottomLeft = { {m_collider.pos.x + offset, m_collider.pos.y + m_collider.size.y}, {0, 1} };
		m_bottomRight = { {m_collider.pos.x + m_collider.size.x - offset, m_collider.pos.y + m_collider.size.y}, {0, 1} };
		m_topLeft = { {m_collider.pos.x + offset, m_collider.pos.y}, {0, -1} };
		m_topRight = { {m_collider.pos.x + m_collider.size.x - offset, m_collider.pos.y}, {0, -1} };
		m_leftBottom = { {m_collider.pos.x, m_collider.pos.y + m_collider.size.y - offset}, {-1, 0} };
		m_leftTop = { {m_collider.pos.x, m_collider.pos.y + offset}, {-1, 0} };
		m_rightBottom = { {m_collider.pos.x + m_collider.size.x, m_collider.pos.y + m_collider.size.y - offset}, {1, 0} };
		m_rightTop = { {m_collider.pos.x + m_collider.size.x, m_collider.pos.y + offset}, {1, 0} };
	}


	void dae::ColliderComponent::PerformCollisionTests()
	{
		bool wasCollidingBottomLeft = false;
		bool wasCollidingBottomRight = false;
		bool wasCollidingTopLeft = false;
		bool wasCollidingTopRight = false;
		bool wasCollidingLeftBottom = false;
		bool wasCollidingLeftTop = false;
		bool wasCollidingRightBottom = false;
		bool wasCollidingRightTop = false;

		for (const auto component : m_colliderComponents)
		{
			if (component == this)
				continue;


			if (IsColliding(component->m_collider))
			{

				DispatchCollisionEvents(component);

				ResolveCollision(component);
			}


			if (component->m_type == ColliderType::Trigger)
				continue;
			HitResult r;

			// Check collisions for each ray probably a better way
			// TODO improve
			if (RayVsRect(m_bottomLeft, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingBottomLeft = true;
			}
			if (RayVsRect(m_bottomRight, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingBottomRight = true;
			}
			if (RayVsRect(m_topLeft, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingTopLeft = true;
			}
			if (RayVsRect(m_topRight, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingTopRight = true;
			}
			if (RayVsRect(m_leftBottom, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingLeftBottom = true;
			}
			if (RayVsRect(m_leftTop, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingLeftTop = true;
			}
			if (RayVsRect(m_rightBottom, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingRightBottom = true;
			}
			if (RayVsRect(m_rightTop, component->m_collider, r) && r.hitDistance < 1.0f)
			{
				wasCollidingRightTop = true;
			}
		}

		// Update the collision flags based on whether any collision was detected
		m_isCollidingBottom = wasCollidingBottomLeft || wasCollidingBottomRight;
		m_isCollidingTop = wasCollidingTopLeft || wasCollidingTopRight;
		m_isCollidingLeft = wasCollidingLeftBottom || wasCollidingLeftTop;
		m_isCollidingRight = wasCollidingRightBottom || wasCollidingRightTop;

		// Update the both collision flags
		m_isCollidingAllBottom = wasCollidingBottomLeft && wasCollidingBottomRight;
		m_isCollidingAllTop = wasCollidingTopLeft && wasCollidingTopRight;
		m_isCollidingAllLeft = wasCollidingLeftBottom && wasCollidingLeftTop;
		m_isCollidingAllRight = wasCollidingRightBottom && wasCollidingRightTop;
	}

	bool dae::ColliderComponent::IsColliding(const Collider& other) const
	{
		return (m_collider.pos.x < other.pos.x + other.size.x && m_collider.pos.x + m_collider.size.x > other.pos.x && m_collider.pos.y < other.pos.y + other.size.y && m_collider.pos.y + m_collider.size.y > other.pos.y);
	}

	void dae::ColliderComponent::ResolveCollision(ColliderComponent* other)
	{
		auto otherCollider = other->m_collider;
		// Calculate the overlap on each side
		float overlapLeft = m_collider.pos.x + m_collider.size.x - otherCollider.pos.x;
		float overlapRight = otherCollider.pos.x + otherCollider.size.x - m_collider.pos.x;
		float overlapTop = m_collider.pos.y + m_collider.size.y - otherCollider.pos.y;
		float overlapBottom = otherCollider.pos.y + otherCollider.size.y - m_collider.pos.y;

		// Check if the colliders are actually overlapping
		if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
		{
			if (m_isInAir && other->m_type == ColliderType::Platform)
			{
				// Ignore the collision
				return;
			}
			if (other->m_type == ColliderType::Trigger)
			{
				return;
			}

			// Find the smallest overlap
			float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

			// Adjust the position based on the smallest overlap
			if (minOverlap == overlapLeft)
			{
				// Move the collider to the left
				m_collider.pos.x = otherCollider.pos.x - m_collider.size.x - 1;
			}
			else if (minOverlap == overlapRight)
			{
				// Move the collider to the right
				m_collider.pos.x = otherCollider.pos.x + otherCollider.size.x + 1;
			}
			else if (minOverlap == overlapTop)
			{
				// Move the collider to the top
				m_collider.pos.y = otherCollider.pos.y - m_collider.size.y - 1;
			}
			else if (minOverlap == overlapBottom)
			{
				// Move the collider to the bottom
				m_collider.pos.y = otherCollider.pos.y + otherCollider.size.y + 1;
			}

			// Update the position of the owner transform
			GetOwner()->SetLocalPosition(m_collider.pos.x, m_collider.pos.y, 0);
		}
	}

	void ColliderComponent::DispatchCollisionEvents(ColliderComponent* other)
	{
		for (auto* observer : m_pObservers)
		{
			if (observer)
			{
				observer->OnCollision(this, other);
			}
		}
	}
}