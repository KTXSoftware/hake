#pragma once

#include "Path.h"
#include <vector>

namespace hake {
	void executeHaxe(kake::Path haxeDirectory, kake::Path directory, std::string backendDir, std::string language, std::vector<std::string> options);
}
