#pragma once

// Forward declarations.
struct GLFWwindow;

namespace Input
{
	void Initialize(GLFWwindow* window);

	bool IsKeyDown(int key);
}

static GLFWwindow* g_window;
