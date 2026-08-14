#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>

namespace dae
{
	class GameObject;

	class ShootBubbleComponent final : public BaseComponent
	{
	public:
		ShootBubbleComponent(GameObject* owner, std::vector<GameObject*>& bubbles);
		virtual ~ShootBubbleComponent() override = default;

		ShootBubbleComponent(const ShootBubbleComponent& other) = delete;
		ShootBubbleComponent(ShootBubbleComponent&& other) = delete;
		ShootBubbleComponent& operator=(const ShootBubbleComponent& other) = delete;
		ShootBubbleComponent& operator=(ShootBubbleComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		void Shoot() const;

	private:
		std::vector<GameObject*>& m_bubbles;
	};
}