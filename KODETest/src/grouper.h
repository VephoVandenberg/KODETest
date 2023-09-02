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
		void writeGroupsToFile(const char* path, const GroupKinds kind);
		void clearGroups();

		Grouper(const Grouper&) = delete;
		Grouper& operator=(const Grouper&) = delete;
		Grouper(Grouper&&) = delete;
		Grouper& operator=(Grouper&&) = delete;

	private:
		void groupByDistance(const std::vector<Object>& objects);
		void groupByName(const std::vector<Object>& objects);
		void groupByTime(const std::vector<Object>& objects);
		void groupByType(const std::vector<Object>& objects);

		template<typename T>
		void sortGroups(std::map<T, std::vector<Object>>& groups, Comparotor compare);
		template<typename T>
		void writeGroups(const std::map<T, std::vector<Object>>& groups, std::ofstream& file);
		template<typename T>
		void clearGroup(std::map<T, std::vector<Object>>& groups);

		std::map<char, std::vector<Object>> m_nameGroups;
		std::map<float, std::vector<Object>> m_distanceGroups;
		std::map<TypeTime, std::vector<Object>> m_timerGroups;
		std::map<const char*, std::vector<Object>> m_typeGroups;
		
	};

	template<typename T>
	void Grouper::sortGroups(std::map<T, std::vector<Object>>& groups, Comparotor compare)
	{
		for (auto& group : groups)
		{
			std::sort(group.second.begin(), group.second.end(), compare);
		}
	}

	template<typename T>
	void Grouper::writeGroups(const std::map<T, std::vector<Object>>& groups, std::ofstream& file)
	{
		for (auto& group : groups)
		{
			for (auto& obj : group.second)
			{
				file << obj;
			}
		}
	}

	template<typename T>
	void Grouper::clearGroup(std::map<T, std::vector<Object>>& groups)
	{
		for (auto& group : groups)
		{
			group.second.clear();
		}
	}
}
