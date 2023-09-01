#include <iostream>

#include "grouper.h"

using namespace Base;

namespace DistanceKeys
{
	constexpr size_t g_lessHundred = 100;
	constexpr size_t g_lessThousand = 1000;
	constexpr size_t g_lessTenThousand = 10000;
	constexpr size_t g_more = g_lessTenThousand + 1;
}

void Grouper::groupAndSort(std::vector<Object>& objects, const GroupKinds kind)
{
	// First group the objects

	switch (kind)
	{
	case GroupKinds::DISTANCE:
	{
		groupByDistance(objects);
		for (auto& group : m_distanceGroups)
		{
			std::sort(group.second.begin(), group.second.end(), s_fComprotors[kind]);
		}

		for (auto& group : m_distanceGroups)
		{
			for (auto& obj : group.second)
			{
				std::cout << obj << std::endl;
			}
		}
	}break;

	case GroupKinds::LETTER:
	{
		groupByLetter(objects);
	}break;

	case GroupKinds::TIMER:
		break;

	case GroupKinds::TYPE:
		break;
	}
}

void Grouper::groupByLetter(std::vector<Object>& objects)
{
	for (auto& obj : objects)
	{
		if (obj.m_name[0] >= 'À' && obj.m_name[0] <= 'ß')
		{

		}
		else
		{

		}
	}
}

void Grouper::groupByDistance(std::vector<Object>& objects)
{
	for (size_t iObj = 0; iObj < objects.size(); iObj++)
	{
		auto d = objects[iObj].getDistance();

		if (d < DistanceKeys::g_lessHundred)
		{
			m_distanceGroups[DistanceKeys::g_lessHundred].push_back(objects[iObj]);
		}
		else if (d < DistanceKeys::g_lessThousand)
		{
			m_distanceGroups[DistanceKeys::g_lessThousand].push_back(objects[iObj]);
		}
		else if (d < DistanceKeys::g_lessTenThousand)
		{
			m_distanceGroups[DistanceKeys::g_lessTenThousand].push_back(objects[iObj]);
		}
		else
		{
			m_distanceGroups[DistanceKeys::g_more].push_back(objects[iObj]);
		}
	}
}
