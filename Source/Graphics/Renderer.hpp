#pragma once

#include "Precompiled.hpp"

#include "SpriteBatch.hpp"

//
// Renderer
//

class Renderer
{
public:
	Renderer(int screen_width, int screen_height);
	~Renderer();

	void Clear();

	void Prepare();
	void Cleanup();

	void Zoom(float dz);

	SpriteBatch& GetSpriteBatch();

private:
	SpriteBatch m_sprite_batch;
	int m_screen_width;
	int m_screen_height;
	float m_zoom;
};
