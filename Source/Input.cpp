#include "Input.hpp"

#include "Precompiled.hpp"

void Input::Initialize(GLFWwindow* window)
{
	g_window = window;

	for (int i = 0; i < 500; i++)
	{
		g_keys_last[i] = false;
		g_keys_current[i] = false;
	}
}

void Input::Reset()
{
	for (int i = 0; i < 500; i++)
	{
		g_keys_last[i] = g_keys_current[i];
		g_keys_current[i] = false;
	}
}

void Input::Update()
{
	for (int i = 0; i < 500; i++)
	{
		if (IsKeyDown(i))
			g_keys_current[i] = true;
	}
}

bool Input::IsKeyDown(int key)
{
	return glfwGetKey(g_window, key) == GLFW_PRESS;
}

bool Input::IsKeyDownNew(int key)
{
	return IsKeyDown(key) && !WasKeyDown(key);
}

bool Input::WasKeyDown(int key)
{
	return g_keys_last[key];
}
