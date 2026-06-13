#pragma once
#include <memory>

namespace game
{
	class MovementSystem;

	class MovementObserver
	{
	public:
		MovementObserver() = default;
		virtual ~MovementObserver() = default;
		virtual void Fall() = 0;
	};
}
