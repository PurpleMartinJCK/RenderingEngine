#include "Random.h"

#include <stdlib.h>
#include <time.h>

void SeedRandomNumberGenerator()
{
	srand((unsigned int)(time(0)));
}

float RandomRangef(float min, float max)
{
	return min + ((max - min) * rand()) / (RAND_MAX + 1.0f);
}

int RandomRangei(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}
