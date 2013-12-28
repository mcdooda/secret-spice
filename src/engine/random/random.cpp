#include <ctime>
#include <cstdlib>
#include "random.h"

namespace engine
{
namespace random
{

static int seed;

int rint(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float rfloat(float min, float max)
{
	return (float) rand() / RAND_MAX * (max - min) + min;
}

void resetSeed()
{
	srand(seed);
}

void setSeed(int newSeed)
{
	srand(newSeed);
}

/* private */

void open()
{
	seed = time(NULL);
	srand(seed);
}

void close()
{

}

} // random
} // engine


