
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <chrono>

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
	switch (kind)
	{
	case GroupKinds::DISTANCE:
		clearGroup<float>(m_distanceGroups);
		groupByDistance(objects);
		sortGroups<float>(m_distanceGroups, s_fComparotors[kind]);
		break;

	case GroupKinds::NAME:
		clearGroup<char>(m_nameGroups);
		groupByName(objects);
		sortGroups<char>(m_nameGroups, s_fComparotors[kind]);
		break;

	case GroupKinds::TIMER:
		clearGroup<TypeTime>(m_timerGroups);
		groupByTime(objects);
		sortGroups<TypeTime>(m_timerGroups, s_fComparotors[kind]);
		break;

	case GroupKinds::TYPE:
		clearGroup<const char*>(m_typeGroups);
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

void Grouper::groupByTime(const std::vector<Object>& objects)
{
	std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm today = *gmtime(&currentTime);
	
	for (auto& obj : objects)
	{
		std::time_t t = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::time_point(
				std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(obj.m_timer))));

		std::tm date = *gmtime(&t);

		if (today.tm_year == date.tm_year &&
			today.tm_yday == date.tm_yday)
		{
			m_timerGroups[TypeTime::TODAY].push_back(obj);
		}
		else if (today.tm_year == date.tm_year &&
			today.tm_yday - date.tm_yday == 1)
		{
			m_timerGroups[TypeTime::YESTERDAY].push_back(obj);
		}
		else if (today.tm_year == date.tm_year &&
			today.tm_yday - date.tm_yday < 7 &&
			today.tm_wday > date.tm_wday)
		{
			m_timerGroups[TypeTime::THIS_WEEK].push_back(obj);
		}
		else if (today.tm_year == date.tm_year &&
			today.tm_mon == date.tm_mon)
		{
			m_timerGroups[TypeTime::THIS_MONTH].push_back(obj);
		}
		else if (today.tm_year == date.tm_year)
		{
			m_timerGroups[TypeTime::THIS_YEAR].push_back(obj);
		}
		else
		{
			m_timerGroups[TypeTime::EARLIER].push_back(obj);
		}
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

void Grouper::writeGroupsToFile(const std::string& path, const GroupKinds kind)
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
		for (auto& group : m_timerGroups)
		{
			for (auto& obj : group.second)
			{
				std::time_t t = std::chrono::system_clock::to_time_t(
					std::chrono::system_clock::time_point(
						std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(obj.m_timer))));

				std::cout << ctime(&t) << std::endl;
			}
		}
		writeGroups<TypeTime>(m_timerGroups, file);
		break;
	}

	file.close();
}

void Grouper::clearGroups()
{
	clearGroup<float>(m_distanceGroups);
	clearGroup<char>(m_nameGroups);
	clearGroup<TypeTime>(m_timerGroups);
	clearGroup<const char*>(m_typeGroups);
}
