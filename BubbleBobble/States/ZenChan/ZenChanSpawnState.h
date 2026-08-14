#pragma once

#include "BubbleBobble/States/StateComponent.h"

namespace dae
{
	class ZenChanSpawnState final : public State
	{
	public:
		explicit ZenChanSpawnState(GameObject* owner);
		~ZenChanSpawnState() override = default;

		void OnEnter() override;
		void OnExit() override;
		void Update(const float& deltaTime) override;
	};
}