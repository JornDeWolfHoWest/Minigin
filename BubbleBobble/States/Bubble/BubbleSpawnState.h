#pragma once
#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class BubbleSpawnState final : public State
	{
	public:
		explicit BubbleSpawnState(GameObject* owner);
		~BubbleSpawnState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;
	};
}