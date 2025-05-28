#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		virtual ~Subject() {

		}

		void AddObserver(Observer* observer)
		{
			observers.push_back(observer);
		}

		void RemoveObserver(Observer* observer)
		{
			observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
		}

	protected:
		void Notify(const Event& event)
		{
			for (Observer* observer : observers)
			{
				observer->Update(event);
			}
		}

	private:
		std::vector<Observer*> observers;
	};
}
