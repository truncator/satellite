#include "SpriteBatch.hpp"

SpriteBatch::SpriteBatch(unsigned int size) :
	m_vbo(0),
	m_vao(0),
	m_drawing(false),
	m_batch_size(size),
	m_current_size(0),
	m_vertex_data(m_batch_size * sizeof(SpriteBatch::Sprite), 0.0f),
	m_batch_count(0)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_batch_size * sizeof(SpriteBatch::Sprite), nullptr, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteBatch::~SpriteBatch()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void SpriteBatch::Begin()
{
	assert(!m_drawing);
	m_drawing = true;
}

void SpriteBatch::End()
{
	assert(m_drawing);
	m_drawing = false;

	Flush();

	m_batch_count = 0;
}

void SpriteBatch::DrawQuad(int x, int y, int width, int height, float rotation, int u, int v, int tw, int th)
{
	assert(m_drawing);

	// Get the current index into the queued vertex data vector.
	int index = m_current_size * sizeof(Sprite);

	// Construct a model matrix for the quad.
	glm::mat4 model_matrix = glm::translate(glm::mat4(), glm::vec3(x + width / 2, y + height / 2, 0));
	model_matrix = glm::rotate(model_matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::translate(model_matrix, glm::vec3(-width / 2, -height / 2, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(width, height, 0.0f));

	// Transform the quad.
	glm::vec3 bottom_left  = glm::vec3(model_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	glm::vec3 bottom_right = glm::vec3(model_matrix * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	glm::vec3 top_right    = glm::vec3(model_matrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	glm::vec3 top_left     = glm::vec3(model_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// Fill the vertex data queue.
	m_vertex_data[index + 0] = bottom_left.x;
	m_vertex_data[index + 1] = bottom_left.y;
	m_vertex_data[index + 2] = 0.0f;

	m_vertex_data[index + 3] = (float)u / 1024;
	m_vertex_data[index + 4] = (float)v / 1024;

	m_vertex_data[index + 5] = bottom_right.x;
	m_vertex_data[index + 6] = bottom_right.y;
	m_vertex_data[index + 7] = 0.0f;

	m_vertex_data[index + 8] = (float)(u + tw) / 1024;
	m_vertex_data[index + 9] = (float)v / 1024;

	m_vertex_data[index + 10] = top_right.x;
	m_vertex_data[index + 11] = top_right.y;
	m_vertex_data[index + 12] = 0.0f;

	m_vertex_data[index + 13] = (float)(u + tw) / 1024;
	m_vertex_data[index + 14] = (float)(v + th) / 1024;

	m_vertex_data[index + 15] = top_left.x;
	m_vertex_data[index + 16] = top_left.y;
	m_vertex_data[index + 17] = 0.0f;

	m_vertex_data[index + 18] = (float)u / 1024;
	m_vertex_data[index + 19] = (float)(v + th) / 1024;

	// Move to the next index.
	m_current_size++;

	// Check if the batch is full.
	if (m_current_size >= m_batch_size)
		Flush();
}

void SpriteBatch::Flush()
{
	if (m_current_size == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Buffer the queued vertex data.
	glBufferData(GL_ARRAY_BUFFER, m_batch_size * sizeof(SpriteBatch::Sprite), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_current_size * sizeof(SpriteBatch::Sprite), &m_vertex_data[0]);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Submit a draw call.
	glBindVertexArray(m_vao);
	glDrawArrays(GL_QUADS, 0, m_current_size * 4);
	glBindVertexArray(0);

	// Reset batch state.
	m_current_size = 0;
	m_batch_count++;
}
