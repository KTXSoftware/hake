#include "Asset.h"

using namespace hake::json;

Asset::Asset() {
	id = kake::UUID::randomUUID().toString();
	scale = 1.0f;
}
	
std::string Asset::toString() {
	return name;
}
