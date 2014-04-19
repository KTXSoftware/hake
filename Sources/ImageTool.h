#pragma once

#include "Json.h"
#include "Path.h"

namespace hake {
	void exportImage(kmd::Path from, kmd::Path to, Json::Value& asset, bool premultiplyAlpha = false);
}
