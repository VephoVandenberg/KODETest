#pragma once

#include <vector>

#include "object.h"

namespace Base
{
	class Grouper;

	class App final
	{
	public:
		App();
		~App() = default;

		void run();

		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;

	private:
		void init();
		
		std::vector<Object> m_objects = {};

		bool m_isRunning = false;
	};
}