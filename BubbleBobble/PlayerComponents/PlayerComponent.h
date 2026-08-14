#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class AnimationComponent;

	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(GameObject* owner, int playerNumber, const glm::vec3& direction);
		virtual ~PlayerComponent() override = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		bool IsMovingHorizontally() { return m_moveDirection.x != 0.f; }
		void SetMoveSpeed(float speed) { m_speed = speed; }
		const glm::vec3& GetSpawnPosition() const { return m_spawnPosition; }
		const glm::vec3& GetSpawnDirection() const { return m_spawnDirection; }
		int GetPlayerNumber() const { return m_playerNumber; }

		GameObject* GetGameObject() const { return GetOwner(); }

	private:
		int m_playerNumber{};
		int m_srcSize{ 16 };
		int m_dstSize{ 32 };
		float m_speed{ 64 };
		float m_jumpForce{ 200 };
		glm::vec3 m_spawnPosition{};
		std::string m_playerSpriteSheet{};
		std::vector<GameObject*> m_bubbles{ 16 };
		glm::vec3 m_spawnDirection{};
		glm::vec3 m_moveDirection{ 0.f };

		AnimationComponent* m_animationComponent{ nullptr };
	};
}