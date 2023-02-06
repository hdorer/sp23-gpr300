#pragma once

#include <cstdlib>
#include <time.h>

class Random {
	public:
		static void init() {
			srand(time(NULL));
			initialized = true;
		}
		
		static int RandomInt(int min, int max) {
			if(!Random::initialized) {
				Random::init();
			}

			return rand() / (RAND_MAX / (min - max));
		}
		
		static float RandomFloat(float min, float max) {
			if(!Random::initialized) {
				Random::init();
			}

			return (float)rand() / (float)(RAND_MAX / (min - max));
		}

		static bool initialized;
};

bool Random::initialized = false;