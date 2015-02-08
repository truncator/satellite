#include "Renderer.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

Renderer::Renderer(int screen_width, int screen_height) :
	m_sprite_batch(1000),
	m_screen_width(screen_width),
	m_screen_height(screen_height),
	m_zoom(1.0f)
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Prepare()
{
	Clear();

	float left = 0.0f - ((m_zoom - 1.0f) * m_screen_width / 2.0f);
	float right = m_screen_width + ((m_zoom - 1.0f) * m_screen_width / 2.0f);
	float bottom = m_screen_height + ((m_zoom - 1.0f) * m_screen_width / 4.0f);
	float top = 0.0f - ((m_zoom - 1.0f) * m_screen_height / 2.0f);
	glm::mat4 projection_matrix = glm::ortho<float>(left, right, bottom, top, 0.0f, 1.0f);

	Shader::Bind("line");
	Shader::SetUniformMatrix("projection_view", projection_matrix);
	Shader::Bind("base");
	Shader::SetUniformMatrix("projection_view", projection_matrix);

	Texture::Bind("space");
}

void Renderer::Cleanup()
{
	Texture::Unbind();
	Shader::Unbind("base");
}

void Renderer::Zoom(float dz)
{
	m_zoom += dz;

	if (m_zoom < 0.5f)
		m_zoom = 0.5f;
}

SpriteBatch& Renderer::GetSpriteBatch()
{
	return m_sprite_batch;
}
