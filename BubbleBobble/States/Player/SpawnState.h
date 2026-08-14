#pragma once
#include "BubbleBobble/States/StateComponent.h"
#include <glm/vec3.hpp>

namespace dae
{
	class SpawnState final : public State
	{
	public:
		explicit SpawnState(GameObject* owner, const glm::vec3& spawnPos, const glm::vec3& spawnDirection, int playerNumber);

		~SpawnState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update(const float& deltaTime) override;

	private:
		glm::vec3 m_spawnPos{};
		glm::vec3 m_spawnDir{};
		int m_playerNumber;
	};
}