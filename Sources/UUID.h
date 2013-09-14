#pragma once

#include "u128.h"
#include <string>

namespace kake {
	struct UUID {
	public:
		static UUID randomUUID();
		UUID();
		UUID(u128 value);
		UUID(std::string string);
		std::string toString();
		bool operator==(UUID id);
		bool operator!=(UUID id);
		bool operator<(const UUID& other) const;
		bool isValid() const;
		unsigned hash() const;
	private:
		u128 value;
	};
}
