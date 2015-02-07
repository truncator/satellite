#pragma once

#include "Precompiled.hpp"

class LineRenderer
{
public:
	struct Line
	{
		glm::vec2 start;
		glm::vec2 end;
		glm::vec3 color;

		Line() :
			start(0.0f, 0.0f), end(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f)
		{
		}

		Line(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color) :
			start(start), end(end), color(color)
		{
		}
	};

public:
	LineRenderer();
	~LineRenderer();

	void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color);
	void Draw();

private:
	std::vector<Line> m_lines;
	unsigned int m_size;

	GLuint m_vao;
};
