#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <chrono>

#include "grouper.h"
#include "app.h"

using namespace Base;

constexpr size_t g_maxObjects = 2048;

App::App()
	: m_isRunning(true)
	, m_currReaderPath("")
	, m_currWriterPath("")
{
	init();
}

void App::init()
{
	std::setlocale(LC_ALL, "");
	m_objects.reserve(g_maxObjects);
	m_grouper = std::make_unique<Grouper>();
}

void App::run()
{
	char choice;

	std::cout
		<< "This app reads objects from a .txt file in a format:\n "
		<< "\tName CoordinateX coordinateY Type Time\n"
		<< "Program handles types, such as: Человек, Машина, Здание, Животное, Разное.\n"
		<< "|===================================================|\n"
		<< "Here is represented the functionality of the program: " << std::endl;

	while (m_isRunning)
	{
		std::cout
			<< "1.Read objects from file\n"
			<< "2.Add object to objects\n"
			<< "3.Group and sort objects\n"
			<< "4.Write to file\n"
			<< "5.Clear objects\n"
			<< "6.Clear groups\n"
			<< "7.Exit\n" 
			<< "|===================================================|" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case '1': 
		{
			std::string path;
			std::cout << "Input the path: ";
			std::cin >> path;

			if (path == m_currReaderPath)
			{
				std::cout << "This file has been read already, and the objects are loaded." << std::endl;
			}
			else
			{
				m_currReaderPath = path;
				readObjectsFromFile(path);
			}
		} break;

		case '2':
		{
			Object obj;

			std::cout << "Name: ";
			std::cin >> obj.m_name;

			std::cout << "X: ";
			std::cin >> std::defaultfloat >> obj.m_x;
			if (!std::cin)
			{
				std::cout << "Invalid input." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			std::cout << "Y: ";
			std::cin >> std::defaultfloat >> obj.m_y;
			if (!std::cin)
			{
				std::cout << "Invalid input." << std::endl;
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			
			std::cout << "Type: ";
			std::cin >> obj.m_type;

			obj.m_timer = 
				static_cast<double>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

			m_objects.push_back(obj);

		} break;

		case '3':
		{
			std::cout
				<< "|===================================================|\n"
				<< "You have to chose the type you want to group objects by(By default groups Distance):\n"
				<< "1.Group by distance\n"
				<< "2.Group by time\n"
				<< "3.Group by name\n"
				<< "4.Group by type\n"
				<< "Your choice: ";
			std::cin >> choice;

			switch (choice)
			{
			case '1':
				m_groupToken = GroupKinds::DISTANCE;
				break;

			case '2':
				m_groupToken = GroupKinds::TIMER;
				break;

			case '3':
				m_groupToken = GroupKinds::NAME;
				break;

			case '4':
				m_groupToken = GroupKinds::TYPE;
				break;

			default:
				std::cout << "Your input is obscure, so grouping stays by distance." << std::endl;
				break;
			}

			m_grouper->groupAndSort(m_objects, m_groupToken);
		} break;

		case '4':
		{
			std::cout << "Input the path: ";
			std::cin >> m_currWriterPath;
			m_grouper->writeGroupsToFile(m_currWriterPath, m_groupToken);
		} break;

		case '5':
			m_objects.clear();
		break;

		case '6':
			m_grouper->clearGroups();
		break;

		case '7':
			m_isRunning = false;
			break;

		default:
			std::cout << "Invalid choice." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
}

void App::readObjectsFromFile(const std::string& path)
{
	if (!m_objects.empty())
	{
		m_objects.clear();
	}

	m_reader.open(path);
	if (m_reader.is_open())
	{
		std::string str;
		while (std::getline(m_reader, str))
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

			m_objects.emplace_back(obj);
		}
		m_reader.close();

		std::cout << "Objects have been read successfully." << std::endl;
	}
	else
	{
		std::cout << "Could not open the file." << std::endl;
	}
}
