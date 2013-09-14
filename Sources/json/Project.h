#pragma once

#include "Asset.h"
#include "Game.h"
#include "Room.h"
#include "Shader.h"
#include <vector>

namespace hake {
	namespace json {
		class Project {
		public:
			int format;
			Game* game;
			std::vector<Asset*> assets;
			std::vector<Room*> rooms;
			std::vector<Shader*> shaders;
		};
	}
}
