#include "LevelCube.h"

#include <GameObject.h>
#include "LevelCubeActivator.h"
#include "Level.h"
#include "MovementSystem.h"
#include "../Enums.h"
#include <ResourceManager.h>

game::LevelCube::LevelCube(dae::GameObject* owner, LevelType type, Level* level, int row, int col,
	const glm::vec3& topMiddle, const glm::vec3& rightMiddle, const glm::vec3& leftMiddle) :
	Walkable(owner, level, row, col, topMiddle, rightMiddle, leftMiddle),
	m_State(0),
	m_MaxStates(MaxStates(type)),
	m_Textures(3),
	m_Type(type)
{

	m_LevelCubeObservers = std::vector<LevelCubeObserver*>();

	m_RenderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
	if (m_RenderComponent == nullptr)
	{
		throw std::runtime_error("LevelCube requires a RenderComponent.");
	}
}

void game::LevelCube::SetTexture(std::string textureName, size_t index)
{
	if (index >= m_Textures.size())
	{
		return;
	}
	m_Textures[index] = textureName;
}

game::Walkable::WalkableType game::LevelCube::GetWalkableType()
{
	return WalkableType::LevelCube;
}

void game::LevelCube::StepOn(MovementSystem* movement)
{
	if (movement == nullptr)
	{
		return;
	}

	auto activator = movement->GetGameObject()->GetComponent<game::LevelCubeActivator>();

	StepOn(activator->GetForward());
}

void game::LevelCube::NextLevel()
{
	m_State = 0;
	switch (m_Type)
	{
	case LevelType::Single:
		m_Type = LevelType::Double;
		break;
	case LevelType::Double:
		m_Type = LevelType::Cycle;
		break;
	case LevelType::Cycle:
		m_Type = LevelType::Single;
		break;
	default:
		m_Type = LevelType::Single;
	}
	m_MaxStates = MaxStates(m_Type);
	SetCurrentTexture();
}

void game::LevelCube::AddObserver(LevelCubeObserver* observer)
{
	m_LevelCubeObservers.push_back(observer);
}

void game::LevelCube::StepOn(bool forward)
{
	switch (m_Type)
	{
	case LevelType::Single:
		StepOnStandard(forward);
		break;
	case LevelType::Double:
		StepOnStandard(forward);
		break;
	case LevelType::Cycle:
		StepOnCycle(forward);
		break;
	}
}

size_t game::LevelCube::MaxStates(LevelType type) const
{
	switch (type)
	{
	case LevelType::Single:
		return 2;
	case LevelType::Double:
		return 3;
	case LevelType::Cycle:
		return 2;
	default:
		return 1;
	}
}

void game::LevelCube::SetCurrentTexture()
{
	m_RenderComponent->SetTexture(m_Textures[m_State]);
}

void game::LevelCube::StepOnStandard(bool forward)
{
	if (forward)
	{
		if (m_State >= m_MaxStates - 1) return;

		++m_State;

		NotifyObservers(
			m_State == m_MaxStates - 1
			? &LevelCubeObserver::CubeDone
			: &LevelCubeObserver::CubeActivated);

		SetCurrentTexture();
		return;
	}

	if (m_State == 0) return;

	NotifyObservers(
		m_State == m_MaxStates - 1
		? &LevelCubeObserver::CubeUndone
		: &LevelCubeObserver::CubeActivated);

	--m_State;
	SetCurrentTexture();
}

void game::LevelCube::StepOnCycle(bool forward)
{
	bool undone = false;
	if (m_State == m_MaxStates - 1)
	{
		NotifyObservers(&LevelCubeObserver::CubeUndone);
		undone = true;
	}
	m_State += forward ? 1 : -1;
	if (forward)
	{
		m_State %= m_MaxStates;
	}
	else if (m_State >= m_MaxStates)
	{
		m_State = m_MaxStates - 1;
	}
	if (m_State == m_MaxStates - 1)
	{
		NotifyObservers(&LevelCubeObserver::CubeDone);
	}
	else if (!undone)
	{
		NotifyObservers(&LevelCubeObserver::CubeActivated);
	}
	SetCurrentTexture();
}

void game::LevelCube::NotifyObservers(std::function<void(LevelCubeObserver*)> observerFunction)
{
	for (auto* observer : m_LevelCubeObservers)
	{
		if (observer)
		{
			observerFunction(observer);
		}
	}
}
