#include "Walkable.h"

#include <utility>
#include "Level.h"
#include <GameObject.h>
#include "MovementSystem.h"


game::Walkable::Walkable(dae::GameObject* owner, Level* level, int row, int col, const glm::vec3& topMiddle,
	const glm::vec3& rightMiddle, const glm::vec3& leftMiddle) :
	BaseComponent(owner),
	m_TopMiddle(topMiddle),
	m_RightMiddle(rightMiddle),
	m_LeftMiddle(leftMiddle),
	m_Level(level),
	m_Row(row),
	m_Column(col)

{}

game::Walkable::~Walkable()
{}

const glm::vec3& game::Walkable::GetMiddleOffset(Side side) const
{
	switch (side)
	{
	case Side::Top:
		return m_TopMiddle;
	case Side::Right:
		return m_RightMiddle;
	case Side::Left:
		return m_LeftMiddle;
	default:
		return m_TopMiddle;
	}
}

game::Walkable* game::Walkable::GetWalkable(Side side, Direction direction)
{
	if (m_Level)
	{
		return m_Level->GetWalkable(side, direction, m_Row, m_Column);
	}
	return nullptr;
}

int game::Walkable::GetLevelSize() const
{
	if (m_Level)
	{
		return m_Level->GetLevelSize();
	}
	return 0;
}

int game::Walkable::GetDistanceTo(const std::shared_ptr<Walkable>& other) const
{
	int otherRow = other->GetRow();
	int otherCol = other->GetColumn();

	return abs(m_Row - m_Column - (otherRow - otherCol)) + abs(m_Column - otherCol);
}
