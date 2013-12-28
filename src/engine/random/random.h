#ifndef ENGINE_RANDOM_H
#define ENGINE_RANDOM_H

namespace engine
{
namespace random
{

int rint(int min, int max);
float rfloat(float min, float max);
void resetSeed();
void setSeed(int newSeed);

/* private */
void open();
void close();

} // random
} // engine

#endif // ENGINE_RANDOM_H


