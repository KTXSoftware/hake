#pragma once

#include <string>
#include <vector>

namespace hake {
	namespace json {
		class Room {
		public:
			std::string id;
			std::string name;
			std::string parent;
			std::vector<std::string> neighbours;
			std::vector<std::string> assets;
		};
	}
}
