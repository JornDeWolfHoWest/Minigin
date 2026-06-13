#pragma once
#include <BaseComponent.h>
#include <glm/glm.hpp>
#include <GameObject.h>

namespace game
{
	class MovementSystem;
	enum class Direction;
	enum class Side;
	class Level;

	class Walkable : public dae::BaseComponent
	{
	public:
		enum class WalkableType
		{
			LevelCube,
			Disc
		};

		Walkable(dae::GameObject* owner, Level* level, int row, int col, const glm::vec3& topMiddle = glm::vec3(0, 0, 0),
			const glm::vec3& rightMiddle = glm::vec3(0, 0, 0), const glm::vec3& leftMiddle = glm::vec3(0, 0, 0));
		virtual ~Walkable() = 0;

		const glm::vec3& GetMiddleOffset(Side side) const;

		Walkable* GetWalkable(Side side, Direction direction);

		int GetColumn() const { return m_Column; }
		int GetRow() const { return m_Row; }
		int GetLevelSize() const;

		virtual WalkableType GetWalkableType() = 0;

		virtual void StepOn(MovementSystem*)
		{}

		virtual void NextLevel()
		{}

		int GetDistanceTo(const std::shared_ptr<Walkable>& other) const;

		bool IsBeingRemoved() {
			return GetOwner()->IsMarkedForDeletion();
		}
		dae::GameObject* GetGameObject() {
			return GetOwner();
		}

	private:
		glm::vec3 m_TopMiddle;
		glm::vec3 m_RightMiddle;
		glm::vec3 m_LeftMiddle;

	protected:
		Level* m_Level;

	private:
		int m_Row;
		int m_Column;
	};
}
