#pragma once

#include "Precompiled.hpp"

//
// Sprite Batch
//     Batches sprite quads into a VBO to reduce draw calls.
//

class SpriteBatch
{
private:

	//
	// Sprite Vertex
	//     Used only for determining batch size and indices.
	//

	struct SpriteVertex
	{
		GLfloat m_position[3];
		GLfloat m_uv[2];
	};

public:
	SpriteBatch(unsigned int size);
	~SpriteBatch();

	// Batch state.
	void Begin();
	void End();

	void DrawQuad(int x, int y, int width, int height, float rotation, int u, int v, int tw, int th, float depth);

private:
	// Buffer queued vertex data and submit a draw call.
	void Flush();

private:
	GLuint m_vbo;
	GLuint m_vao;

	// Batch state.
	bool m_drawing;

	// Vertex data queued to be batched.
	unsigned int m_batch_size;
	unsigned int m_current_size;
	std::vector<GLfloat> m_vertex_data;

	// Number of batches made during the current frame.
	unsigned int m_batch_count;
};
