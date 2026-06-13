#include "Disc.h"
#include "MovementSystem.h"
#include "GameObject.h"
#include "Level.h"
#include <algorithm>


game::Disc::Disc(dae::GameObject* owner, Level* level, int row, int col, const glm::vec3& topMiddle, float moveTime) :
	Walkable(owner, level, row, col, topMiddle),
	m_Movement(nullptr),
	m_MoveTimer(0),
	m_MoveTime(moveTime)
{}

void game::Disc::Update(const float& deltaTime)
{
	if (m_MoveTimer <= 0)
	{
		return;
	}
	m_MoveTimer -= deltaTime;

	if (m_MoveTimer <= 0)
	{
		DoneMoving();
	}
}

game::Walkable::WalkableType game::Disc::GetWalkableType()
{
	return WalkableType::Disc;
}

void game::Disc::StepOn(MovementSystem* movement)
{
	if (movement == nullptr)
	{
		return;
	}
	m_Movement = movement;
	m_Movement->CanMove(false);
	m_MoveTimer = m_MoveTime;
	GetOwner()->SetActive(true);
}

void game::Disc::NextLevel()
{
	m_MoveTimer = 0;
	GetOwner()->SetActive(false);

	m_Level->AddScore(m_DISCSCORE);
}

void game::Disc::AddObserver(DiscObserver* observer)
{
	m_DiscObservers.push_back(observer);
}

void game::Disc::DoneMoving()
{
	for (auto* observer : m_DiscObservers)
	{
		if (observer)
		{
			observer->DiscDoneMoving();
		}
	}

	GetOwner()->SetActive(false);
	if (m_Movement == nullptr)
	{
		return;
	}

	m_Movement->CanMove(true);
	m_Movement->SetCurrentWalkable(m_Level->GetTopCube());
}
