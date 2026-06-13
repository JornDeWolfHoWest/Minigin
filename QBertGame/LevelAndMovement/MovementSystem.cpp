#include "MovementSystem.h"
#include "Walkable.h"
#include "GameObject.h"
#include "MovementObserver.h"
#include <algorithm>
#include <glm/glm.hpp>

game::MovementSystem::MovementSystem(dae::GameObject* owner, Walkable* currentWalkable, const glm::vec3& positionOffset, Side side,
	float moveTime, bool enemy) :
	m_CurrentWalkable(currentWalkable),
	m_PositionOffset(positionOffset),
	m_MoveTimer(0),
	m_Moving(false),
	m_StartWalkable(currentWalkable),
	m_NextWalkable(nullptr),
	m_Side(side),
	m_MoveTime(moveTime),
	m_StartMoveTime(moveTime),
	m_CanMove(true),
	m_Enemy(enemy), BaseComponent(owner)
{}

void game::MovementSystem::Update(const float& deltaTime)
{
	if (!m_Moving)
	{
		return;
	}
	m_MoveTimer -= deltaTime;
	if (m_NextWalkable != nullptr)
	{
		auto goToPos = m_NextWalkable->GetGameObject()->GetWorldPosition().GetPosition() - m_CurrentWalkable->GetGameObject()->GetWorldPosition().GetPosition();

		auto comingFromPos = glm::vec3{ 0, 0, 0 };

		float t = 1.0f - (m_MoveTimer / m_MoveTime);
		t = std::clamp(t, 0.0f, 1.0f);

		auto newPos = comingFromPos + (goToPos + comingFromPos) * t;
		newPos += glm::vec3{ 8, 8, 8 };
		GetOwner()->SetLocalPosition(newPos.x, newPos.y, 999);
	}

	if (m_MoveTimer <= 0)
	{
		SetCurrentWalkable(m_NextWalkable);
	}
}

void game::MovementSystem::Move(Direction direction)
{
	if (!m_CanMove || m_MoveTimer > 0)
	{
		return;
	}

	m_NextWalkable = m_CurrentWalkable->GetWalkable(m_Side, direction);
	if (m_Enemy && m_NextWalkable && m_NextWalkable->GetWalkableType() !=
		Walkable::WalkableType::LevelCube)
	{
		m_NextWalkable = nullptr;
	}
	m_MoveTimer = m_MoveTime;
	m_Moving = true;
}

void game::MovementSystem::CanMove(bool canMove)
{
	m_CanMove = canMove;
	if (!m_CanMove)
	{
		m_Moving = false;
	}
}

void game::MovementSystem::SetCurrentWalkable(Walkable* walkable)
{
	m_Moving = false;
	m_CurrentWalkable = walkable;
	if (m_CurrentWalkable == nullptr)
	{
		Fall();
		return;
	}
	MoveToCurrent();
	m_CurrentWalkable->StepOn(this);
}

void game::MovementSystem::Respawn(bool toStart)
{
	if (m_CurrentWalkable || toStart)
	{
		if (!m_StartWalkable)
		{
			return;
		}
		m_CurrentWalkable = m_StartWalkable;
	}
	MoveToCurrent();
	m_CanMove = true;
	m_MoveTimer = 0;
	m_Moving = false;
}

void game::MovementSystem::AddObserver(MovementObserver* observer)
{
	m_MovementObservers.push_back(observer);
}
void game::MovementSystem::MoveToCurrent()
{
	if (m_CurrentWalkable == nullptr)
	{
		m_CurrentWalkable = m_StartWalkable;
	}

	auto currentGameObject = m_CurrentWalkable->GetGameObject();
	if (!currentGameObject || !GetOwner())
	{
		return;
	}
	auto child = GetOwner()->GetParent()->DetachChild(GetOwner());
	currentGameObject->AddChild(std::move(child));

	auto& middle = m_CurrentWalkable->GetMiddleOffset(m_Side);
	auto pos = middle + m_PositionOffset;

	GetOwner()->SetLocalPosition(pos.x, pos.y, pos.z);
}

void game::MovementSystem::Fall()
{
	m_CurrentWalkable = nullptr;

	for (MovementObserver* movementObserver : m_MovementObservers)
	{
		if (movementObserver != nullptr)
		{
			movementObserver->Fall();
		}
	}
}
