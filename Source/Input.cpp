#include "Input.hpp"

#include "Precompiled.hpp"

void Input::Initialize(GLFWwindow* window)
{
	g_window = window;
}

bool Input::IsKeyDown(int key)
{
	return glfwGetKey(g_window, key) == GLFW_PRESS;
}
