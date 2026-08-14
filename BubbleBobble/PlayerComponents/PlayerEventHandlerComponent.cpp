#include "PlayerEventHandlerComponent.h"
#include <iostream>
#include <memory>

#include "GameObject.h"
#include "GameSettings.h"
#include "HealthComponent.h"
#include "BubbleBobble/States/Player/HitState.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "SpriteComponent.h"
#include "BubbleBobble/States/StateComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "Scene.h"
#include "BubbleBobble/Bubble/BubbleComponent.h"
#include "BubbleBobble/Enemy/ZenChanComponent.h"
#include "BubbleBobble/States/StateComponent.h"
#include "BubbleBobble/Food/FoodComponent.h"

namespace dae
{
	PlayerEventHandlerComponent::PlayerEventHandlerComponent(GameObject* owner)
		: BaseComponent(owner)
	{}

	void PlayerEventHandlerComponent::Update(const float&) {}
	void PlayerEventHandlerComponent::FixedUpdate() {}
	void PlayerEventHandlerComponent::Render() const {}

	void PlayerEventHandlerComponent::OnPlayerSpawn(int )
	{
	}

	void PlayerEventHandlerComponent::OnPlayerIdle()
	{
		auto* activeScene = SceneManager::GetInstance().GetActiveScene();

		bool enemiesExist = activeScene->GetComponent<ZenChanComponent>() ||
			activeScene->GetComponent<BubbleComponent>();

		if (!enemiesExist)
		{
			if (auto* scoreComp = GetOwner()->GetComponent<ScoreComponent>())
			{
				GameSettings::GetInstance().SaveScore(scoreComp->GetScore());
			}

			int currentLevel = GameSettings::GetInstance().GetCurrentLevel();
			if (currentLevel == 3)
			{
				GameSettings::GetInstance().SetGameState(GameSettings::GameState::Gameover, -1);
			}

			currentLevel = (currentLevel % 3) + 1;
			GameSettings::GetInstance().SetChangeLevelFlag(currentLevel);
		}
	}

	void PlayerEventHandlerComponent::OnPlayerDamaged()
	{
		if (auto* stateComp = GetOwner()->GetComponent<StateComponent>())
		{
			stateComp->SetState("Hit");
		}

		if (auto* healthComp = GetOwner()->GetComponent<HealthComponent>())
		{
			healthComp->Damage(1);
		}
	}

	void PlayerEventHandlerComponent::OnPlayerFall(GameObject* player)
	{
		if (!player) return;

		int playerNum = 1;
		if (auto* playerComp = player->GetComponent<PlayerComponent>())
			playerNum = playerComp->GetPlayerNumber();
	}

	void PlayerEventHandlerComponent::OnPlayerMove(GameObject* player)
	{
		if (!player) return;

		int playerNum = 1;
		if (auto* playerComp = player->GetComponent<PlayerComponent>())
			playerNum = playerComp->GetPlayerNumber();
	}

	void PlayerEventHandlerComponent::OnBubblePopEnemy(GameObject* poppedEnemy)
	{
		if (!poppedEnemy) return;

		auto poppedEnemyPos = poppedEnemy->GetLocalPosition().GetPosition();
		bool isZenChan = poppedEnemy->GetComponent<ZenChanComponent>() != nullptr;

		poppedEnemy->MarkForDeletion();

		auto item = std::make_unique<GameObject>();
		item->SetLocalPosition(poppedEnemyPos.x, poppedEnemyPos.y, poppedEnemyPos.z);

		if (isZenChan)
		{
			item->AddComponent(std::make_unique<FoodComponent>(item.get(), 1));
			item->AddComponent(std::make_unique<SpriteComponent>(item.get(), "Sprites/Food/Watermelon.png"));
			item->AddComponent(std::make_unique<ColliderComponent>(item.get(), 16, ColliderType::Trigger));
		}
		else
		{
			// TODO for other enemy setup
			item->AddComponent(std::make_unique<FoodComponent>(item.get(), 2));
			item->AddComponent(std::make_unique<SpriteComponent>(item.get(), "Sprites/Food/Watermelon.png"));
			item->AddComponent(std::make_unique<ColliderComponent>(item.get(), 32, ColliderType::Trigger));
		}

		SceneManager::GetInstance().GetActiveScene()->Add(std::move(item));
	}

	void PlayerEventHandlerComponent::OnItemCollected(GameObject* item, GameObject* player, int itemType)
	{
		if (!item || !player) return;

		if (auto* scoreComp = player->GetComponent<ScoreComponent>())
		{
			if (itemType == 1)
				scoreComp->AddToScore(100);
			else
				scoreComp->AddToScore(200);
		}

		item->MarkForDeletion();

		auto* activeScene = SceneManager::GetInstance().GetActiveScene();


		if (!activeScene->GetComponent<ZenChanComponent>() ||
			activeScene->GetComponent<FoodComponent>())
		{
			if (auto* scoreComp = GetOwner()->GetComponent<ScoreComponent>())
			{
				GameSettings::GetInstance().SaveScore(scoreComp->GetScore());
			}

			int currentLevel = GameSettings::GetInstance().GetCurrentLevel();
			if (currentLevel == 3)
			{
				GameSettings::GetInstance().SetGameState(GameSettings::GameState::Gameover, -1);
			}

			currentLevel = (currentLevel % 3) + 1;
			GameSettings::GetInstance().SetChangeLevelFlag(currentLevel);
		}
	}

	void PlayerEventHandlerComponent::OnMaitaDamaged(GameObject* )
	{
	}

	void PlayerEventHandlerComponent::UnbindAllControls(int /*playerNumber*/)
	{
		
	}

	void PlayerEventHandlerComponent::BindAllControls(int /*playerNumber*/)
	{
	}

	void PlayerEventHandlerComponent::OnCollision(ColliderComponent* self, ColliderComponent* other)
	{
		if (!self || !other || self == other) return;

		if (other->GetGameObject()->GetComponent<ZenChanComponent>())
		{
			if (other->GetGameObject()->GetComponent<StateComponent>()->GetCurrentStateName() == "Vulnerable")
			{
				// We hit zenchan and he was vurnerable, so we pop him
				OnBubblePopEnemy(other->GetGameObject());
			}
			else
			{
				// We hit zenchan and he wasn't vurnerable, so we take damage
				OnPlayerDamaged();
			}
		}

		if (other->GetGameObject()->GetComponent<FoodComponent>())
		{
			// We hit a food, so we collect it
			OnItemCollected(other->GetGameObject(), self->GetGameObject(), other->GetGameObject()->GetComponent<FoodComponent>()->GetItemType());
		}
	}
}