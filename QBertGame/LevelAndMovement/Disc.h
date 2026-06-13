#pragma once
#include <vector>

#include "Walkable.h"

namespace game
{
	class DiscObserver;

	class Disc : public Walkable
	{
	public:
		Disc(dae::GameObject* owner, Level* level, int row, int col, const glm::vec3& topMiddle, float moveTime = 6.0f);
		virtual ~Disc() = default;

		void Update(const float& deltaTime) override;
		void FixedUpdate() override {}
		void Render() const override {}

		WalkableType GetWalkableType() override;

		void StepOn(MovementSystem* movement) override;

		void NextLevel() override;

		void AddObserver(DiscObserver* observer);

	private:
		void DoneMoving();

		std::vector<DiscObserver*> m_DiscObservers;

		MovementSystem* m_Movement;

		float m_MoveTimer;
		float m_MoveTime;

		static const int m_DISCSCORE{50};
	};
}
