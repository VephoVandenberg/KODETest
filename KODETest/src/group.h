#pragma once

#include <unordered_map>

#include "object.h"

namespace Base
{
	enum class GroupKinds
	{
		NAME,
		DISTANCE,
		TIMER,
		TYPE
	};

	enum class TypeTime
	{
		EARLIER,
		THIS_YEAR,
		THIS_MONTH,
		THIS_WEEK,
		YESTERDAY,
		TODAY,
	};

	enum class ObjType
	{
		HUMAN,
		CAR,
		BUILDING,
		ANIMAL,
		OTHER
	};
	
	using Comparotor = bool (*)(const Object& obj1, const Object& obj2);

	static std::unordered_map<GroupKinds, Comparotor> s_fComparotors = {
		{
			GroupKinds::NAME, 
			[](const Object& obj1, const Object& obj2) {
				return obj1.m_name[0] < obj2.m_name[0]; 
			}
		},
		{
			GroupKinds::DISTANCE,
			[](const Object& obj1, const Object& obj2) {
				return obj1.getDistance() < obj2.getDistance();
			}
		},
		{
			GroupKinds::TIMER,
			[](const Object& obj1, const Object& obj2) {
				return obj1.m_timer < obj2.m_timer;
			}
		},
	};
}