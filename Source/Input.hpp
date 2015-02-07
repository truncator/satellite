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

	void Reset();
	void Update();

	bool IsKeyDown(int key);
	bool IsKeyDownNew(int key);
	bool WasKeyDown(int key);
}

static GLFWwindow* g_window;
static bool g_keys_current[500];
static bool g_keys_last[500];
