#pragma once

#include <string>

namespace Base
{
	struct Object
	{
		float m_x = 0.0f;
		float m_y = 0.0f;
		double m_timer = 0.0f;
		std::string m_type;
		std::string m_name;

		float getDistance() const;
		friend std::ofstream& operator<<(std::ofstream& file, const Object& obj);
		friend std::ostream& operator<<(std::ostream& o, const Object& obj);
	};
}
