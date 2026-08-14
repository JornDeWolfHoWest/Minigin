#include "ZenChanSpawnState.h"

#include <memory>

#include "GameObject.h"
#include "BubbleBobble/States/StateComponent.h"
#include "BubbleBobble/States/ZenChan/ZenChanChaseState.h"

namespace dae
{
	ZenChanSpawnState::ZenChanSpawnState(GameObject* owner)
		: State(owner)
	{}

	void ZenChanSpawnState::OnEnter()
	{}

	void ZenChanSpawnState::OnExit()
	{}

	void ZenChanSpawnState::Update(const float&)
	{
		if (auto stateComp = GetOwner()->GetComponent<StateComponent>())
		{
			stateComp->SetState("Chase");
		}
	}
}