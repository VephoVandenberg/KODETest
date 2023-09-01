#include <fstream>
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
		groupByDistance(objects);
		sortGroups<float>(m_distanceGroups, s_fComparotors[kind]);
		break;

	case GroupKinds::NAME:
		groupByName(objects);
		sortGroups<char>(m_nameGroups, s_fComparotors[kind]);
		break;

	case GroupKinds::TIMER:
		groupByTime(objects);
		break;

	case GroupKinds::TYPE:
		groupByType(objects);
		sortGroups<const char*>(m_typeGroups, s_fComparotors[kind]);
		break;
	}
}

void Grouper::groupByName(const std::vector<Object>& objects)
{
	for (auto& obj : objects)
	{
		if (obj.m_name[0] >= 'А' && obj.m_name[0] <= 'Я')
		{
			m_nameGroups[obj.m_name[0]].push_back(obj);
		}
		else
		{
			m_nameGroups['#'].push_back(obj);
		}
	}
}

void Grouper::groupByType(const std::vector<Object>& objects)
{
	for (auto& obj : objects)
	{
		if (obj.m_type == "Человек" ||
			obj.m_type == "Машина" ||
			obj.m_type == "Здание" ||
			obj.m_type == "Животное")
		{
			m_typeGroups[obj.m_type.c_str()].push_back(obj);
		}
		else
		{
			m_typeGroups["Разное"].push_back(obj);
		}
	}
}

std::chrono::system_clock::time_point Grouper::doubleToTime(double d)
{
	using namespace std::chrono;
	using namespace date;
	using ddays = duration<double, days::period>;
	return sys_days{ December / 30 / 1899 } + round<system_clock::duration>(ddays{ d });
}

void Grouper::groupByTime(const std::vector<Object>& objects)
{
	using date::operator<<;
	for (auto& obj : objects)
	{
		std::cout << doubleToTime(obj.m_timer) << std::endl;
	}
}

void Grouper::groupByDistance(const std::vector<Object>& objects)
{
	for (auto& obj : objects)
	{
		auto d = obj.getDistance();

		if (d < DistanceKeys::g_lessHundred)
		{
			m_distanceGroups[DistanceKeys::g_lessHundred].push_back(obj);
		}
		else if (d < DistanceKeys::g_lessThousand)
		{
			m_distanceGroups[DistanceKeys::g_lessThousand].push_back(obj);
		}
		else if (d < DistanceKeys::g_lessTenThousand)
		{
			m_distanceGroups[DistanceKeys::g_lessTenThousand].push_back(obj);
		}
		else
		{
			m_distanceGroups[DistanceKeys::g_more].push_back(obj);
		}
	}
}

void Grouper::writeGroupsToFile(const char* path, const GroupKinds kind)
{
	std::ofstream file(path);
	
	if (!file.is_open())
	{
		std::cout << "Could not open " << path << std::endl;
		return;
	}

	switch (kind)
	{
	case GroupKinds::DISTANCE:
		writeGroups<float>(m_distanceGroups, file);
		break;

	case GroupKinds::NAME:
		writeGroups<char>(m_nameGroups, file);
		break;

	case GroupKinds::TYPE:
		writeGroups<const char*>(m_typeGroups, file);
		break;

	case GroupKinds::TIMER:
		writeGroups<double>(m_timerGroups, file);
		break;
	}

	file.close();
}

void Grouper::clearGroups()
{
	clearGroup<float>(m_distanceGroups);
	clearGroup<char>(m_nameGroups);
	clearGroup<double>(m_timerGroups);
	clearGroup<const char*>(m_typeGroups);
}
