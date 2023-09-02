#pragma once

#include <memory>
#include <vector>
#include <fstream>

#include "object.h"
#include "grouper.h"

namespace Base
{
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
		void addObject(const Object& obj);
		void readObjectsFromFile(const std::string& path);
		
		std::vector<Object> m_objects = {};		
		std::unique_ptr<Grouper> m_grouper = nullptr;
		std::ifstream m_reader;
		std::string m_currReaderPath;
		std::string m_currWriterPath;

		GroupKinds m_groupToken = GroupKinds::DISTANCE;

		bool m_isRunning = false;
	};
}
