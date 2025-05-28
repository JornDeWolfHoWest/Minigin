#pragma once

namespace dae
{
	enum class EventType
	{
		HealthChanged,
		ScoreChanged
	};

	class Event
	{
	public:
		Event(EventType type) : m_Type(type) {}
		virtual ~Event() = default;
		EventType GetType() const { return m_Type; }
	private:
		EventType m_Type;
	};
}