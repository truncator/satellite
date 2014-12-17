#pragma once

// Forward declarations.
struct GLFWwindow;

//
// Input
//     Simple wrapper for GLFW input.
//

namespace Input
{
	void Initialize(GLFWwindow* window);

	bool IsKeyDown(int key);
}

static GLFWwindow* g_window;
