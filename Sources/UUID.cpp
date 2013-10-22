#include "UUID.h"
#include "Random.h"
#include <math.h>
#include <stdexcept>

using namespace kake;

namespace {
	int fromHex(char c) {
		if (c >= '0' && c <= '9') return c - '0';
		else if (c >= 'a' && c <= 'f') return c + 10 - 'a';
		else if (c >= 'A' && c <= 'F') return c + 10 - 'A';
		else throw std::runtime_error("not a hex char");
	}

	char toHex(u64 i) {
		if (i < 10) return static_cast<char>(i + '0');
		else return static_cast<char>(i - 10 + 'a');
	}
}

UUID UUID::randomUUID() {
	u64 low = static_cast<u64>(Random::get()) << 32 | static_cast<u64>(Random::get());
	u64 high = static_cast<u64>(Random::get()) << 32 | static_cast<u64>(Random::get());
	return UUID(u128(low, high));
}

UUID::UUID() {

}

UUID::UUID(u128 value) : value(value) {

}

UUID::UUID(std::string string) {
	u64 low = 0;
	int p = 0;
	int i;
	int cut = static_cast<int>(string.length()) - 1 - 12;
	for (i = static_cast<int>(string.length() - 1); i > cut; --i) {
		low += fromHex(string[i]) * (u64)pow(16.0, p);
		++p;
	}
	--i;
	cut -= 5;
	for (; i > cut; --i) {
		low += fromHex(string[i]) * (u64)pow(16.0, p);
		++p;
	}
	--i;
	cut -= 5;
	p = 0;
	u64 high = 0;
	for (; i > cut; --i) {
		high += fromHex(string[i]) * (u64)pow(16.0, p);
		++p;
	}
	--i;
	cut -= 5;
	for (; i > cut; --i) {
		high += fromHex(string[i]) * (u64)pow(16.0, p);
		++p;
	}
	--i;
	cut = 0;
	for (; i >= cut; --i) {
		high += fromHex(string[i]) * (u64)pow(16.0, p);
		++p;
	}
	value = u128(low, high);
}

std::string UUID::toString() {
	u64 low = value.low();
	std::string string;
	for (int i = 0; i < 12; ++i) {
		string = std::string() + toHex(low & 0xf) + string;
		low /= 16;
	}
	string = std::string("-") + string;
	for (int i = 0; i < 4; ++i) {
		string = std::string() + toHex(low & 0xf) + string;
		low /= 16;
	}
	string = std::string("-") + string;
	u64 high = value.high();
	for (int i = 0; i < 4; ++i) {
		string = std::string() + toHex(high & 0xf) + string;
		high /= 16;
	}
	string = std::string("-") + string;
	for (int i = 0; i < 4; ++i) {
		string = std::string() + toHex(high & 0xf) + string;
		high /= 16;
	}
	string = std::string("-") + string;
	for (int i = 0; i < 8; ++i) {
		string = std::string() + toHex(high & 0xf) + string;
		high /= 16;
	}
	return string;
}

bool UUID::operator==(UUID id) {
	return value == id.value;
}

bool UUID::operator!=(UUID id) {
	return value != id.value;
}

bool UUID::operator<(const UUID& id) const {
	return value < id.value;
}

bool UUID::isValid() const {
	return value != 0;
}

unsigned UUID::hash() const {
	return value.hash();;
}
