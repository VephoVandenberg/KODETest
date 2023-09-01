#pragma once

#include <map>
#include <vector>
#include <algorithm>

#include "group.h"

#include "object.h"

namespace Base
{
	class Grouper final
	{
	public:
		Grouper() = default;
		~Grouper() = default;

		void groupAndSort(std::vector<Object>& objects, const GroupKinds kind);

		Grouper(const Grouper&) = delete;
		Grouper& operator=(const Grouper&) = delete;
		Grouper(Grouper&&) = delete;
		Grouper& operator=(Grouper&&) = delete;

	private:
		void groupByDistance(std::vector<Object>& objects);
		void groupByLetter(std::vector<Object>& objects);
		void groupByTime(std::vector<Object>& objects);

		std::map<char, std::vector<Object>> m_letterGroups;
		std::map<float, std::vector<Object>> m_distanceGroups;
		std::map<double, std::vector<Object>> m_timerGroups;
		
	};
}
