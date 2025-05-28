#pragma once
#include "Event.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Update(const Event& event) = 0;
	};
}
