#pragma once
#include "BaseComponent.h"
#include <SDL3/SDL.h>

namespace dae
{
	class SelectorComponent final : public BaseComponent
	{
	public:
		explicit SelectorComponent(GameObject* owner, int controllerIndex = 0, int totalOptions = 3);
		virtual ~SelectorComponent() override = default;

		SelectorComponent(const SelectorComponent& other) = delete;
		SelectorComponent(SelectorComponent&& other) = delete;
		SelectorComponent& operator=(const SelectorComponent& other) = delete;
		SelectorComponent& operator=(SelectorComponent&& other) = delete;

		void Update(const float& ) override {}
		void FixedUpdate() override {}
		void Render() const override {}

		void BindInputs(int controllerIndex);
		void MoveSelection(int offset);
		void Confirm();

	private:
		void UpdatePosition();

		int m_currentSelection{ 0 };
		int m_totalOptions{ 3 };
		int m_controllerIndex{ 0 };
	};
}