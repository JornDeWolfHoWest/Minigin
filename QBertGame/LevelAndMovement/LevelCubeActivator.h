#pragma once
#include "BaseComponent.h"

namespace game
{
	class LevelCubeActivator : public dae::BaseComponent
	{
	public:

		LevelCubeActivator(dae::GameObject* owner, bool forward);
		virtual ~LevelCubeActivator() = default;

		void Update(const float&) override {}
		void FixedUpdate() override {}
		void Render() const override {}

		bool GetForward() const { return m_Forward; }

	private:
		bool m_Forward;
	};
}
