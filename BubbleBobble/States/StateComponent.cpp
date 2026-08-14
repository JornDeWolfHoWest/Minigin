#include "StateComponent.h"

namespace dae
{
	StateComponent::StateComponent(GameObject* owner)
		: BaseComponent(owner)
	{}

	void StateComponent::AddState(std::string stateName, std::unique_ptr<State> newState)
	{
		if (!newState)
		{
			return;
		}
		auto it = m_allStates.find(stateName);
		if (it != m_allStates.end())
		{
			// temp for bug fix
			return;
		}
		m_allStates.insert_or_assign(stateName, std::move(newState));
	}

	void StateComponent::SetState(std::string stateName)
	{

		if (m_currentState)
		{
			if (stateName == GetCurrentStateName()) return; // If the state is already active, do nothing

			m_currentState->OnExit();
		}

		auto it = m_allStates.find(stateName);
		if (it != m_allStates.end())
			m_currentState = it->second.get();
		else
			return; // Smt went wrong

		if (m_currentState)
		{
			m_currentState->OnEnter();
		}
	}

	void StateComponent::Update(const float& deltaTime)
	{
		if (m_currentState)
		{
			m_currentState->Update(deltaTime);
		}
	}

	void StateComponent::FixedUpdate()
	{}

	void StateComponent::Render() const
	{}
}