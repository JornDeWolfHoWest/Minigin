#pragma once
#include "BaseComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"

namespace dae
{
	class GameObject;

	class BubbleEventsListener
	{
	public:
		virtual ~BubbleEventsListener() = default;

		virtual void OnBubbleHitEnemy(GameObject* bubble, GameObject* hitEnemy) = 0;
		virtual void OnBubblePopNoEnemy(GameObject* bubble) = 0;
		virtual void OnBubbleSpawn() = 0;
		virtual void OnBubbleShot() = 0;
		virtual void OnBubblePlayerJump(GameObject* player, GameObject* bubble) = 0;
	};

	class BubbleEventHandlerComponent final : public BaseComponent, public BubbleEventsListener, public CollisionObserver
	{
	public:
		explicit BubbleEventHandlerComponent(GameObject* owner);
		virtual ~BubbleEventHandlerComponent() override = default;

		BubbleEventHandlerComponent(const BubbleEventHandlerComponent& other) = delete;
		BubbleEventHandlerComponent(BubbleEventHandlerComponent&& other) = delete;
		BubbleEventHandlerComponent& operator=(const BubbleEventHandlerComponent& other) = delete;
		BubbleEventHandlerComponent& operator=(BubbleEventHandlerComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {}
		void Render() const override {}

		void OnBubbleHitEnemy(GameObject* bubble, GameObject* hitEnemy) override;
		void OnBubblePopNoEnemy(GameObject* bubble) override;
		void OnBubbleSpawn() override;
		void OnBubbleShot() override;
		void OnBubblePlayerJump(GameObject* player, GameObject* bubble) override;

		void OnCollision(ColliderComponent* self, ColliderComponent* other) override;
	};
}