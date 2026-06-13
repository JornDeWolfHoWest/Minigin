#pragma once
#include <BaseComponent.h>


#include <vector>
#include "level.h"
#include <glm/glm.hpp>


class dae::GameObject;
namespace game
{
	class Walkable;
	class MovementObserver;

	enum class Side
	{
		Top,
		Right,
		Left
	};

	enum class Direction
	{
		Up,
		Right,
		Down,
		Left
	};

	class MovementSystem : public dae::BaseComponent
	{
	public:
		MovementSystem(dae::GameObject* owner, Walkable* currentWalkable, const glm::vec3& positionOffset, Side side,
			float moveTime = 0.75f, bool enemy = true);
		virtual ~MovementSystem() = default;

		void Update(const float& deltatime) override;
		void FixedUpdate() override {}
		void Render() const override {}

		void Move(Direction direction);
		bool CanMove() const { return m_CanMove; }
		void CanMove(bool canMove);
		Walkable* GetCurrentWalkable() const { return m_CurrentWalkable; }
		void SetCurrentWalkable(Walkable* walkable);
		void Respawn(bool toStart = false);

		void AddObserver(MovementObserver* observer);

		void SetPositionOffset(const glm::vec3& offset) { m_PositionOffset = offset; }
		void SetMoveTime(float moveTime) { m_MoveTime = moveTime; }
		void ResetMoveTime() { m_MoveTime = m_StartMoveTime; }

		dae::GameObject* GetGameObject() { return GetOwner(); }

	private:
		void MoveToCurrent();
		void Fall();

		std::vector<MovementObserver*> m_MovementObservers;

		Walkable* m_CurrentWalkable;
		Walkable* m_NextWalkable;
		Walkable* m_StartWalkable;

		glm::vec3 m_PositionOffset;

		Side m_Side;

		float m_MoveTimer;
		float m_MoveTime;
		float m_StartMoveTime;
		bool m_Moving;

		bool m_CanMove;
		bool m_Enemy;
	};
}
