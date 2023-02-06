#include "Random.h"

#include <cstdlib>
#include <time.h>

float Random::RandomFloat(float min, float max) {
	return (float)rand() / (float)(RAND_MAX / (min - max));
}

int Random::RandomInt(int min, int max) {
	return rand() / (RAND_MAX / (min - max));
}

Random::Random() {
	srand(time(NULL));
}