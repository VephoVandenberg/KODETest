#pragma once

#include <unordered_map>

#include "object.h"

namespace Base
{
	enum class GroupKinds
	{
		LETTER,
		DISTANCE,
		TIMER,
		TYPE
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

	static std::unordered_map<GroupKinds, Comparotor> s_fComprotors = {
		{
			GroupKinds::LETTER, 
			[](const Object& obj1, const Object& obj2) {
				return obj1.m_name[0] < obj2.m_name[1]; 
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
				return obj1.getDistance() < obj2.getDistance();
			}
		},
	};
}