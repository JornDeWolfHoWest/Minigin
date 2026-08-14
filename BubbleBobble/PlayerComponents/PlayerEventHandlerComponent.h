#pragma once
#include "BaseComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"

namespace dae
{
	class GameObject;

	class PlayerEventsListener
	{
	public:
		virtual ~PlayerEventsListener() = default;

		virtual void OnPlayerSpawn(int playerNumber) = 0;
		virtual void OnPlayerIdle() = 0;
		virtual void OnPlayerDamaged() = 0;
		virtual void OnPlayerFall(GameObject* player) = 0;
		virtual void OnPlayerMove(GameObject* player) = 0;
	};

	class LevelEventsListener
	{
	public:
		virtual ~LevelEventsListener() = default;

		virtual void OnBubblePopEnemy(GameObject* poppedEnemy) = 0;
		virtual void OnItemCollected(GameObject* item, GameObject* player, int itemType) = 0;
		virtual void OnMaitaDamaged(GameObject* maita) = 0;
	};

	class PlayerEventHandlerComponent final : public BaseComponent, public PlayerEventsListener, public LevelEventsListener, public CollisionObserver
	{
	public:
		explicit PlayerEventHandlerComponent(GameObject* owner);
		virtual ~PlayerEventHandlerComponent() override = default;

		PlayerEventHandlerComponent(const PlayerEventHandlerComponent& other) = delete;
		PlayerEventHandlerComponent(PlayerEventHandlerComponent&& other) = delete;
		PlayerEventHandlerComponent& operator=(const PlayerEventHandlerComponent& other) = delete;
		PlayerEventHandlerComponent& operator=(PlayerEventHandlerComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		void OnPlayerSpawn(int playerNumber) override;
		void OnPlayerIdle() override;
		void OnPlayerDamaged() override;
		void OnPlayerFall(GameObject* player) override;
		void OnPlayerMove(GameObject* player) override;

		void OnBubblePopEnemy(GameObject* poppedEnemy) override;
		void OnItemCollected(GameObject* item, GameObject* player, int itemType) override;
		void OnMaitaDamaged(GameObject* maita) override;

		void OnCollision(ColliderComponent* self, ColliderComponent* other) override;

	private:
		void UnbindAllControls(int playerNumber);
		void BindAllControls(int playerNumber);
	};
}