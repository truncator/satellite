#pragma once

// This file is used for precompiled third party header files.
// Changing this file will force a rebuild of the entire project.

//
// Standard C++
//

#include <cstdio>
#include <ctime>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

//
// Dependencies
//

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stb_image
#include "stb_image.h"

//
// Project
//

#include "../../Source/Random.hpp"
