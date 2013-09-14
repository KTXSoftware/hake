#pragma once

#include "../UUID.h"
#include "Color.h"

namespace hake {
	namespace json {
		class Asset {
		public:
			std::string id;
			std::string type;
			std::string file;
			std::string name;
			float scale;
			Color background;
			bool circle;
	
			Asset();
			std::string toString();
		};
	}
}
