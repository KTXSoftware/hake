#include "Random.h"

using namespace kake;

//MT19937

namespace {
	int MT[624];
	int index = 0;

	void generateNumbers() {
		for (int i = 0; i < 624; ++i) {
			int y = (MT[i] & 1) + (MT[(i + 1) % 624]) & 0x7fffffff;
			MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
			if ((y % 2) != 0) MT[i] = MT[i] ^ 0x9908b0df;
		}
	}
}

void Random::init(int seed) {
	MT[0] = seed;
	for (int i = 1; i < 624; ++i) MT[i] = 0x6c078965 * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
}

int Random::get() {
	if (index == 0) generateNumbers();

	int y = MT[index];
	y = y ^ (y >> 11);
	y = y ^ ((y << 7) & (0x9d2c5680));
	y = y ^ ((y << 15) & (0xefc60000));
	y = y ^ (y >> 18);

	index = (index + 1) % 624;
	return y;
}

int Random::get(int max) {
	return Random::get() % (max + 1);
}

int Random::get(int min, int max) {
	return Random::get() % (max + 1 - min) + min;
}
