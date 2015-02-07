#include "Random.hpp"

#include "Precompiled.hpp"

void Random::Initialize()
{
	srand(time(0));
}

float Random::Float()
{
	std::uniform_real_distribution<> dis(0.0f, 1.0f);
	return dis(g_gen);
}

float Random::Float(float min, float max)
{
	return min + Random::Float() * (max - min);
}

int Random::Int(int min, int max)
{
	return min + Float() * (max - min);
}
