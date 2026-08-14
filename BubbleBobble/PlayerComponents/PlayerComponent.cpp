#include "PlayerComponent.h"
#include "AnimationComponent.h"
#include "BubbleBobble/Level/ColliderComponent.h"
#include "GameObject.h"
#include "BubbleBobble/PlayerComponents/HealthComponent.h"
#include "HealthObserverComponent.h"
#include "BubbleBobble/States/Player/IdleState.h"
#include "BubbleBobble/States/Player/JumpState.h"
#include "BubbleBobble/States/Player/ShootState.h"
#include "BubbleBobble/States/Player/SpawnState.h"
#include "BubbleBobble/States/Player/MoveState.h"
#include "BubbleBobble/States/Player/HitState.h"
#include "BubbleBobble/States/Player/FallState.h"
#include "BubbleBobble/States/StateComponent.h"
#include "InputManager.h"
#include "BubbleBobble/PlayerComponents/PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScoreObserverComponent.h"
#include "BubbleBobble/PlayerComponents/ScoreComponent.h"
#include "BubbleBobble/PlayerComponents/ShootBubbleComponent.h"
#include "BubbleBobble/Bubble/BubbleComponent.h"
#include "BubbleBobble/AnimationComponent.h"

namespace dae
{
	PlayerComponent::PlayerComponent(GameObject* owner, int playerNumber, const glm::vec3& direction) :
		BaseComponent(owner),
		m_playerNumber{ playerNumber },
		m_spawnDirection{ direction }
	{
		if (m_playerNumber == 1)
			m_playerSpriteSheet = "Sprites/Players/BobSpriteSheet.png";
		if (m_playerNumber == 2)
			m_playerSpriteSheet = "Sprites/Players/BobSpriteSheet.png";

		owner->AddComponent(std::make_unique<AnimationComponent>(owner, m_playerSpriteSheet));
		m_animationComponent = owner->GetComponent<AnimationComponent>();

		m_animationComponent->SetDestinationSize({ m_dstSize, m_dstSize });

		const AnimationData walkAnimation{ 0, 4 };
		m_animationComponent->AddAnimation("Walk", walkAnimation);

		const AnimationData idleAnimation{ 0, 2 };
		m_animationComponent->AddAnimation("Idle", idleAnimation);

		const AnimationData jumpUpAnimation{ 1, 2, 16, 0.25f };
		m_animationComponent->AddAnimation("JumpUp", jumpUpAnimation);

		const AnimationData fallDownAnimation{ 2, 2, 16, 0.25f };
		m_animationComponent->AddAnimation("FallDown", fallDownAnimation);

		const AnimationData shootAnimation{ 3, 1, 16, 0.25f };
		m_animationComponent->AddAnimation("Shoot", shootAnimation);

		const AnimationData deathAnimation{ 7, 6, 16, 0.25f };
		m_animationComponent->AddAnimation("Death", deathAnimation);

		// Pull transform data directly from GameObject's value-based Transform
		m_spawnPosition = owner->GetLocalPosition().GetPosition() * glm::vec3{ static_cast<float>(m_srcSize) };

		// Score Setup
		owner->AddComponent(std::make_unique<ScoreComponent>(owner, 0));
		if (auto* scoreObserver = SceneManager::GetInstance().GetActiveScene()->GetComponent<ScoreObserverComponent>())
		{
			owner->GetComponent<ScoreComponent>()->AddObserver(scoreObserver);
		}

		// Health Setup
		owner->AddComponent(std::make_unique<HealthComponent>(owner, 3));
		if (auto* healthObserver = SceneManager::GetInstance().GetActiveScene()->GetComponent<HealthObserverComponent>())
		{
			owner->GetComponent<HealthComponent>()->AddObserver(healthObserver);
		}

		owner->AddComponent(std::make_unique<PlayerEventHandlerComponent>(owner));
		owner->AddComponent(std::make_unique<ColliderComponent>(owner, m_dstSize, ColliderType::Trigger));
		if (auto* colliderComp = owner->GetComponent<ColliderComponent>())
		{
			colliderComp->AddObserver(owner->GetComponent<PlayerEventHandlerComponent>());
		}

		owner->AddComponent(std::make_unique<RigidBodyComponent>(owner));

		// Core Logic Components Setup

		owner->AddComponent(std::make_unique<StateComponent>(owner));
		if (auto* stateComp = owner->GetComponent<StateComponent>())
		{
			stateComp->AddState("Idle", std::make_unique<IdleState>(owner, m_playerNumber, this));
			stateComp->AddState("Move", std::make_unique<MoveState>(owner, m_playerNumber, this));

			stateComp->AddState("Hit", std::make_unique<HitState>(owner, m_playerNumber));
			stateComp->AddState("Fall", std::make_unique<FallState>(owner, m_playerNumber));
			stateComp->AddState("Spawn", std::make_unique<SpawnState>(owner, m_spawnPosition, m_spawnDirection, m_playerNumber));
			stateComp->AddState("Jump", std::make_unique<JumpState>(owner, m_playerNumber));
			stateComp->AddState("Shoot", std::make_unique<ShootState>(owner, m_playerNumber));
			
			stateComp->SetState("Spawn");
		}

		for (int i{}; i < 16; ++i)
		{
			auto bubble = std::make_unique<GameObject>();
			bubble->AddComponent(std::make_unique<BubbleComponent>(bubble.get(), m_playerSpriteSheet, this));
			m_bubbles[i] = bubble.get();

			bubble.get()->GetComponent<StateComponent>()->SetState("Spawn");

			SceneManager::GetInstance().GetActiveScene()->Add(std::move(bubble));
		}
		
		owner->AddComponent(std::make_unique<ShootBubbleComponent>(owner, m_bubbles));

		auto moveAction = [this](const glm::vec3& dir) {
			m_moveDirection = dir;
			};

		auto jumpAction = [owner, playerNum = m_playerNumber]() {
			if (auto* stateComp = owner->GetComponent<StateComponent>())
			{
				stateComp->SetState("Jump");
			}
			};

		auto shootAction = [owner, playerNum = m_playerNumber]() {
			if (auto* stateComp = owner->GetComponent<StateComponent>())
			{
				stateComp->SetState("Shoot");
			}
			};

		// Input Setup
		auto& inputManager = InputManager::GetInstance();

		if (m_playerNumber == 1)
		{
			// Keyboard (Player 1)
			inputManager.AddKeyCommand(SDLK_LEFT, [moveAction]() { moveAction(glm::vec3{ -1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddKeyCommand(SDLK_RIGHT, [moveAction]() { moveAction(glm::vec3{ 1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddKeyCommand(SDLK_UP, {}, jumpAction);
			inputManager.AddKeyCommand(SDLK_SPACE, {}, shootAction);

			// Controller 0 (Player 1)
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_DPAD_LEFT, 0, [moveAction]() { moveAction(glm::vec3{ -1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_DPAD_RIGHT, 0, [moveAction]() { moveAction(glm::vec3{ 1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_A, 0, {}, jumpAction);
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_B, 0, {}, shootAction);
		}
		else if (m_playerNumber == 2)
		{
			// Controller 1 (Player 2)
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_DPAD_LEFT, 1, [moveAction]() { moveAction(glm::vec3{ -1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_DPAD_RIGHT, 1, [moveAction]() { moveAction(glm::vec3{ 1.f, 0.f, 0.f }); }, [moveAction]() { moveAction(glm::vec3{ 0.f, 0.f, 0.f }); });
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_A, 1, {}, jumpAction);
			inputManager.AddControllerKeyCommand(XINPUT_GAMEPAD_B, 1, {}, shootAction);
		}
	}

	void PlayerComponent::Update(const float& deltaTime)
	{
		if (m_moveDirection != glm::vec3{ 0.f })
		{
			auto* owner = GetOwner();
			auto* collider = owner->GetComponent<ColliderComponent>();
			if (!collider)
				return;

			bool goingLeftWhileTouchingLeft = collider->IsCollidingLeft() && m_moveDirection.x < 0.0f;
			bool goingRightWhileTouchingRight = collider->IsCollidingRight() && m_moveDirection.x > 0.0f;

			if (!(goingLeftWhileTouchingLeft || goingRightWhileTouchingRight))
			{
				glm::vec3 pos = owner->GetLocalPosition().GetPosition();
				pos += m_moveDirection * deltaTime * m_speed;
				owner->SetLocalPosition(pos.x, pos.y, pos.z);

				if (m_animationComponent)
				{
					m_animationComponent->SetForwardDirection({ m_moveDirection.x, 0.0f, 0.0f });
				}
			}
		}
	}

	void PlayerComponent::FixedUpdate()
	{}

	void PlayerComponent::Render() const
	{}
}