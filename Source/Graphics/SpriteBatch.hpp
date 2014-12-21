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
		GLfloat m_color[3];
		GLfloat m_uv[2];
	};

public:
	SpriteBatch(unsigned int size);
	~SpriteBatch();

	// Batch state.
	void Begin();
	void End();

	void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec3& color, const glm::vec4& uv, float depth);

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
