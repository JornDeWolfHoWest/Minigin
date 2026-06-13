#include "Level.h"

#include <numeric>
#include <utility>

#include "Walkable.h"
#include "Level.h"
#include "GameObject.h"
#include "Score.h"
#include <GameObject.h>
#include <BaseComponent.h>
#include "MovementSystem.h"


void game::Level::Update(const float&)
{}

game::Level::Level(dae::GameObject* owner, int levelSize, int discAmount, game::Score* score) :
	BaseComponent(owner),
	m_Level(LevelIndex(levelSize, -1)),
	m_Score(std::move(score)),
	m_LevelSize(levelSize),
	m_DiscAmount(discAmount),
	m_Win(LevelIndex(levelSize - 2, -1)),
	m_WinCounter(0),
	m_LevelCounter(0),
	m_MaxLevel(2)
{}


void game::Level::SetLevel(Walkable* walkable, int row, int col)
{
	auto index = LevelIndex(row, col);
	if (index > m_Level.size())
	{
		return;
	}
	m_Level[index] = walkable;
}

game::Walkable* game::Level::GetTopCube() const
{
	return m_Level[LevelIndex(0, 0)];
}

game::Walkable* game::Level::GetTopRightCube() const
{
	return m_Level[LevelIndex(1, 1)];
}

game::Walkable* game::Level::GetTopLeftCube() const
{
	return m_Level[LevelIndex(1, 0)];
}

game::Walkable* game::Level::GetBottomRightCube() const
{
	return m_Level[LevelIndex(m_LevelSize - 1, m_LevelSize - 1)];
}

game::Walkable* game::Level::GetBottomLeftCube() const
{
	return m_Level[LevelIndex(m_LevelSize - 1, 0)];
}

game::Walkable* game::Level::GetWalkable(Side side, Direction direction, int row, int col) const
{
	switch (side)
	{
	case game::Side::Top:
		return GetWalkableTop(direction, row, col);
	case game::Side::Right:
		return GetWalkableRight(direction, row, col);
	case game::Side::Left:
		return GetWalkableLeft(direction, row, col);
	default:
		return nullptr;
	}
}

unsigned int game::Level::LevelIndex(int row, int col)
{
	row += 2;
	col += 1;
	return (row * row - row) / 2 + row + col;
}

void game::Level::CubeDone()
{
	++m_WinCounter;
	AddScore(m_CubeScore);
	if (m_WinCounter >= m_Win)
	{
		if (m_LevelCounter >= m_MaxLevel)
		{
			NotifyObservers(&LevelObserver::GameComplete);
			return;
		}
		NextLevel();
	}
}

void game::Level::CubeActivated()
{
	AddScore(m_CubeScore);
}

void game::Level::CubeUndone()
{
	--m_WinCounter;
}

void game::Level::DiscDoneMoving()
{
	NotifyObservers(&LevelObserver::LevelDisc);
}

void game::Level::AddScore(unsigned score)
{
	m_Score->AddScore(score);
}

void game::Level::AddObserver(LevelObserver* observer)
{
	m_LevelObservers.push_back(observer);
}

game::Walkable* game::Level::GetWalkableTop(Direction direction, int row, int col) const
{
	switch (direction)
	{
	case Direction::Up:
		return m_Level[LevelIndex(row - 1, col)];
	case Direction::Right:
		if (row >= m_LevelSize - 1)
		{
			return nullptr;
		}
		return m_Level[LevelIndex(row + 1, col + 1)];
	case Direction::Down:
		if (row >= m_LevelSize - 1)
		{
			return nullptr;
		}
		return m_Level[LevelIndex(row + 1, col)];
	case Direction::Left:
		return m_Level[LevelIndex(row - 1, col - 1)];
	default:
		return nullptr;
	}
}

game::Walkable* game::Level::GetWalkableRight(Direction direction, int row, int col) const
{
	switch (direction)
	{
	case Direction::Up:
		return m_Level[LevelIndex(row - 1, col - 1)];
	case Direction::Right:
		return m_Level[LevelIndex(row, col + 1)];
	case Direction::Down:
		if (row >= m_LevelSize - 1)
		{
			return nullptr;
		}
		return m_Level[LevelIndex(row + 1, col + 1)];
	case Direction::Left:
		return m_Level[LevelIndex(row, col - 1)];
	default:
		return nullptr;
	}
}

game::Walkable* game::Level::GetWalkableLeft(Direction direction, int row, int col) const
{
	switch (direction)
	{
	case Direction::Up:
		return m_Level[LevelIndex(row - 1, col)];
	case Direction::Right:
		return m_Level[LevelIndex(row, col + 1)];
	case Direction::Down:
		if (row >= m_LevelSize - 1)
		{
			return nullptr;
		}
		return m_Level[LevelIndex(row + 1, col)];
	case Direction::Left:
		return m_Level[LevelIndex(row, col - 1)];
	default:
		return nullptr;
	}
}

void game::Level::ActivateDiscs()
{
	std::vector<int> leftDiscs(m_LevelSize - 1);
	std::vector<int> rightDiscs(m_LevelSize - 1);
	std::iota(std::begin(leftDiscs), std::end(leftDiscs), 0);
	std::iota(std::begin(rightDiscs), std::end(rightDiscs), 0);
	bool left = true;
	for (int i = 0; i < m_DiscAmount; ++i)
	{
		unsigned int index = rand() % (left ? leftDiscs.size() : rightDiscs.size());
		int row = left ? leftDiscs[index] : rightDiscs[index];
		int col = left ? -1 : row + 1;

		auto walkable = m_Level[LevelIndex(row, col)];
		if (!walkable)
		{
			return;
		}
		if (walkable->IsBeingRemoved())
		{
			RemoveUsedDisc(left ? leftDiscs : rightDiscs, row);
			left = !left;
			continue;
		}

		walkable->GetGameObject()->SetActive(true);
		RemoveUsedDisc(left ? leftDiscs : rightDiscs, row);
		left = !left;
	}
}

void game::Level::RemoveUsedDisc(std::vector<int>& discs, int row) const
{
	discs.erase(std::remove(std::begin(discs), std::end(discs), row), std::end(discs));
}

void game::Level::NextLevel()
{
	m_WinCounter = 0;
	++m_LevelCounter;
	for (auto& walkable : m_Level)
	{
		if (walkable == nullptr)
		{
			continue;
		}
		walkable->NextLevel();
	}
	ActivateDiscs();
	NotifyObservers(&LevelObserver::NextLevel);
}

void game::Level::NotifyObservers(std::function<void(LevelObserver*)> observerFunction)
{
	for (LevelObserver* observer : m_LevelObservers)
	{
		if (observer != nullptr)
		{
			observerFunction(observer);
		}
	}
}
