#pragma once

#include "BaseComponent.h"

namespace dae
{
	class ColliderComponent;

	class RigidBodyComponent final : public BaseComponent
	{
	public:
		explicit RigidBodyComponent(GameObject* owner);
		~RigidBodyComponent() override = default;

		RigidBodyComponent(const RigidBodyComponent& other) = delete;
		RigidBodyComponent(RigidBodyComponent&& other) = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&& other) = delete;

		// BaseComponent overrides
		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		void Jump();

		[[nodiscard]] float GetVerticalVelocity() const { return m_verticalVelocity; }

	private:
		ColliderComponent* m_collider{ nullptr };

		bool m_isJumping{ false };
		float m_verticalVelocity{ 0.0f };

		float m_gravity{ 200.0f };
		float m_horizontalAirControlForce{ 50.0f };
		float m_idleAirForce{ 100.0f };
		float m_jumpVelocity{ -170.0f };
	};
}