#include "Random.hpp"

#include "Precompiled.hpp"

void Random::Initialize()
{
	srand(time(0));
}

float Random::Float()
{
	return (float)rand() / RAND_MAX;
}

float Random::Float(float min, float max)
{
	return min + Float() * (max - min);
}

int Random::Int(int min, int max)
{
	return min + Float() * (max - min);
}
