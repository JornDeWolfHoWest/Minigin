#include "RigidBodyComponent.h"

#include <algorithm>

#include "BubbleBobble/Level/ColliderComponent.h"
#include "GameObject.h"

namespace dae
{
	RigidBodyComponent::RigidBodyComponent(GameObject* owner)
		: BaseComponent(owner)
	{}

	void RigidBodyComponent::Update(const float& deltaTime)
	{
		if (!IsActive())
		{
			return;
		}

		if (!m_collider)
		{
			m_collider = GetOwner()->GetComponent<ColliderComponent>();
		}

		const bool isCollidingBottom = m_collider && m_collider->IsCollidingBottom();

		if (isCollidingBottom)
		{
			if (!m_isJumping)
			{
				m_verticalVelocity = 0.0f;
			}
		}
		else
		{
			// Apply gravity
			m_verticalVelocity += m_gravity * deltaTime;
		}

		m_verticalVelocity = std::clamp(m_verticalVelocity, -200.0f, 200.0f);

		Transform transform = GetOwner()->GetLocalPosition();
		const auto& pos = transform.GetPosition();

		GetOwner()->SetLocalPosition(pos.x, pos.y + (m_verticalVelocity * deltaTime), pos.z);

		if (isCollidingBottom && m_verticalVelocity >= 0.0f)
		{
			m_isJumping = false;
		}
	}

	void RigidBodyComponent::FixedUpdate()
	{}

	void RigidBodyComponent::Render() const
	{}

	void RigidBodyComponent::Jump()
	{
		this;
		if (!m_collider)
		{
			m_collider = GetOwner()->GetComponent<ColliderComponent>();
		}

		if (m_collider && m_collider->IsCollidingBottom())
		{
			m_verticalVelocity = m_jumpVelocity;
			m_isJumping = true;
		}
	}
}