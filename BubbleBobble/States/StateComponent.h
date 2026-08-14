#pragma once

#include "BaseComponent.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace dae
{
	class GameObject;

	class State
	{
	public:
		virtual ~State() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void Update(const float& deltaTime) = 0;


	protected:
		explicit State(GameObject* owner) : m_owner{ owner } {}
		[[nodiscard]] GameObject* GetOwner() const { return m_owner; }

	private:
		GameObject* m_owner{ nullptr };
	};

	class StateComponent final : public BaseComponent
	{
	public:
		explicit StateComponent(GameObject* owner);
		~StateComponent() override = default;

		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void AddState(std::string stateName, std::unique_ptr<State> newState);
		void SetState(std::string stateName);
		[[nodiscard]] State* GetCurrentState() const { return m_currentState; }

		void Update(const float& deltaTime) override;
		void FixedUpdate() override;
		void Render() const override;

		[[nodiscard]] std::string GetCurrentStateName() const
		{
			if (!m_currentState)
				return "";

			for (const auto& [name, state] : m_allStates)
			{
				if (state.get() == m_currentState)
					return name;
			}

			return "";
		}
	private:
		State* m_currentState{ nullptr };
		std::unordered_map<std::string, std::unique_ptr<State>> m_allStates{};
	};
}