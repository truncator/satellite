#pragma once

#include "Precompiled.hpp"

//
// Random
//

namespace Random
{
	void Initialize();

	float Float();
	float Float(float min, float max);

	int Int(int min, int max);
}

static std::random_device g_rd;
static std::mt19937 g_gen(g_rd());
