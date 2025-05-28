#pragma once
#include "Event.h"

namespace dae
{
	class HealthChangedEvent : public Event
	{
	public:
		HealthChangedEvent(int health)
			: Event(EventType::HealthChanged), m_Health(health) {}

		int GetHealth() const { return m_Health; }

	private:
		int m_Health;
	};
}
