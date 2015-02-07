#include "LineRenderer.hpp"

#include "Shader.hpp"

LineRenderer::LineRenderer() :
	m_lines(10000, Line()),
	m_size(0),
	m_vao(0)
{
	glGenVertexArrays(1, &m_vao);
}

LineRenderer::~LineRenderer()
{
	glDeleteVertexArrays(1, &m_vao);
}

void LineRenderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color)
{
	assert(m_size < 10000);
	m_lines[m_size++] = Line(start, end, color);
}

void LineRenderer::Draw()
{
	Shader::Bind("line");

	for (const Line& line : m_lines)
	{
		Shader::SetUniformVec2("line_start", line.start);
		Shader::SetUniformVec2("line_end", line.end);
		Shader::SetUniformVec3("line_color", line.color);

		glBindVertexArray(m_vao);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
	}

	Shader::Unbind("line");

	m_size = 0;
}
