#include <iostream>

#include "app.h"

using namespace Base;

constexpr size_t g_maxObjects = 2048;

App::App()
	: m_isRunning(true)
{
	init();
}

void App::init()
{
	std::setlocale(LC_ALL, "");
	m_objects.reserve(g_maxObjects);
}

void App::run()
{
	char choice;

	while (m_isRunning)
	{
		std::cin >> choice;

		std::cout << choice;
	}
}
