#pragma once

#include "Json.h"
#include "Path.h"

namespace hake {
	void exportImage(kake::Path from, kake::Path to, Json::Value& asset);
}
