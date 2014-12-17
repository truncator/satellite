#pragma once

#include "Precompiled.hpp"

//
// Texture
//     Manages textures.
//

namespace Texture
{
	struct Image
	{
		GLuint m_id;
		bool m_binded;

		Image() :
			m_id(0), m_binded(false)
		{
		}
	};

	void Initialize();
	void Load(const std::string& name);

	void Bind(const std::string& name);
}

typedef std::unordered_map<std::string, Texture::Image> TextureList;

static TextureList g_textures;
