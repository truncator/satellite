#pragma once

#include "Precompiled.hpp"

class Renderer
{
private:

	struct Quad
	{
		GLuint m_vbo;
		GLuint m_vao;
	};

public:
	Renderer();
	~Renderer();

	void Clear();

	void FillQuad(int x, int y, int width, int height, float r, float g, float b, float a);
	void RenderQuad(int x, int y, int width, int height, float rotation, int u, int v, int tw, int th);

private:
	Quad m_quad;
};
