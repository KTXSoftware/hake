#pragma once

namespace kake {
	namespace Random {
		void init(int seed);
		int get();
		int get(int max);
		int get(int min, int max);
	}
}