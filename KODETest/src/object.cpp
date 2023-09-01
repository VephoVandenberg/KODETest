#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#include <windows.h>

#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "object.h"

using namespace Base;

std::ofstream& Base::operator<<(std::ofstream& file, const Object& obj)
{
	if (!file.is_open())
	{
		std::cout << "File is not open" << std::endl;
	}

	file << obj.m_name << " "
		<< std::defaultfloat << obj.m_x << " " 
		<< std::defaultfloat << obj.m_y << " " 
		<< obj.m_type << " " 
		<< std::fixed << obj.m_timer << std::endl;

	return file;
}

std::ostream& Base::operator<<(std::ostream& o, const Object& obj)
{
	o << obj.getDistance() << " " << obj.m_name << " "
		<< std::defaultfloat << obj.m_x << " " 
		<< std::defaultfloat << obj.m_y << " " 
		<< obj.m_type << " " 
		<< std::fixed << obj.m_timer;

	return o;
}

float Object::getDistance() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}
