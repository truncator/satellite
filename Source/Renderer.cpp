#include "Renderer.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

Renderer::Renderer()
{
	GLfloat vertex_data[20] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &m_quad.m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_quad.m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_quad.m_vao);
	glBindVertexArray(m_quad.m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_quad.m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_quad.m_vao);
	glDeleteBuffers(1, &m_quad.m_vbo);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FillQuad(int x, int y, int width, int height, float r, float g, float b, float a)
{
	Shader::Bind("fill");

	glm::mat4 model_matrix = glm::scale(glm::translate(glm::mat4(), glm::vec3(x, y, 0.0f)), glm::vec3(width, height, 0));
	glm::mat4 projection_matrix = glm::ortho<float>(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);

	Shader::SetUniformMatrix("projection_view", projection_matrix);
	Shader::SetUniformMatrix("model", model_matrix);
	Shader::SetUniformVec4("color", glm::vec4(r, g, b, a));

	glBindVertexArray(m_quad.m_vao);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

	Shader::Unbind("fill");
}

void Renderer::RenderQuad(int x, int y, int width, int height, float rotation, int u, int v, int tw, int th)
{
	Shader::Bind("base");

	glm::mat4 model_matrix = glm::translate(glm::mat4(), glm::vec3(x + width / 2, y + height / 2, 0));
	model_matrix = glm::rotate(model_matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::translate(model_matrix, glm::vec3(-width / 2, -height / 2, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(width, height, 0));
	glm::mat4 projection_matrix = glm::ortho<float>(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);

	Shader::SetUniformMatrix("projection_view", projection_matrix);
	Shader::SetUniformMatrix("model", model_matrix);
	Shader::SetUniformVec2("tex_offset", glm::vec2((float)u / 1024, (float)v / 1024));
	Shader::SetUniformVec2("tex_size", glm::vec2((float)tw / 1024, (float)th / 1024));
	Texture::Bind("space");

	glBindVertexArray(m_quad.m_vao);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

	Shader::Unbind("base");
}
