#include "Texture.hpp"

#include "Shader.hpp"

void Texture::Initialize()
{
	Load("space");
}

void Texture::Load(const std::string& name)
{
	std::string path = "../../Resource/Texture/" + name + ".png";

	int width, height, channels;
	unsigned char* image_data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (image_data == nullptr)
	{
		printf("Failed to load image: %s\n", path.c_str());
		return;
	}

	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image_data);

	Texture::Image image;
	image.m_id = id;
	image.m_binded = false;

	g_textures.emplace(name, image);
}

void Texture::Bind(const std::string& name)
{
	auto it = g_textures.find(name);
	if (it == g_textures.end())
	{
		printf("Texture not found: %s\n", name.c_str());
		return;
	}

	if (it->second.m_binded)
		return;

	glBindTexture(GL_TEXTURE_2D, it->second.m_id);
	Shader::SetUniformInt("tex", it->second.m_id);
}
