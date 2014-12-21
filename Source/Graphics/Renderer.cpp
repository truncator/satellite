#include "Renderer.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

Renderer::Renderer(int screen_width, int screen_height) :
	m_screen_width(screen_width),
	m_screen_height(screen_height),
	m_sprite_batch(1000)
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

	glm::mat4 projection_matrix = glm::ortho<float>(0.0f, m_screen_width, m_screen_height, 0.0f, 0.0f, 1.0f);

	Shader::Bind("base");
	Shader::SetUniformMatrix("projection_view", projection_matrix);

	Texture::Bind("space");
}

void Renderer::Cleanup()
{
	Texture::Unbind();
	Shader::Unbind("base");
}

SpriteBatch& Renderer::GetSpriteBatch()
{
	return m_sprite_batch;
}
