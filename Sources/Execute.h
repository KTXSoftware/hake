#pragma once

#include <string>
#include <vector>

namespace hake {
	void executeSync(std::string command, std::vector<std::string> arguments, std::string env = "", std::string currentDirectory = "");
}
