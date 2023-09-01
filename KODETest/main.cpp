#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "src/group.h"
#include "src/grouper.h"
#include "src/object.h"

constexpr size_t g_maxObjects = 2048;

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "");

	std::vector<Base::Object> objects;
	objects.reserve(g_maxObjects);

	std::ifstream reader("input.txt");
	
	// Read from file
	if (reader.is_open())
	{
		std::string str;
		while (std::getline(reader, str))
		{
			if (str.length() == 0)
			{
				continue;
			}

			std::istringstream stream(str);

			Base::Object obj;
			stream >> obj.m_name
				>> obj.m_x
				>> obj.m_y
				>> obj.m_type
				>> obj.m_timer;

			objects.emplace_back(obj);
			std::cout << obj << std::endl;
		}
	}

	reader.close();

	// Sort by groups
	std::cout << std::endl;
	Base::Grouper grouper;
	grouper.groupAndSort(objects, Base::GroupKinds::DISTANCE);

	// Write to file
	std::ofstream writer("output.txt");

	for (const auto& obj : objects)
	{
		writer << obj;
	}

	writer.close();

	return 0;
}