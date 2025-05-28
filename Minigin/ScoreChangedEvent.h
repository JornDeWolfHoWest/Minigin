#pragma once
#include "Event.h"

namespace dae
{
	class ScoreChangedEvent : public Event
	{
	public:
		ScoreChangedEvent(int score)
			: Event(EventType::ScoreChanged), m_Score(score) {
		}

		int GetScore() const { return m_Score; }

	private:
		int m_Score;
	};
}
