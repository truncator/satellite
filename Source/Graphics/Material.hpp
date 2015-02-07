#pragma once

#include "Precompiled.hpp"

//
// Material
//

class Material
{
public:
	Material(glm::vec3 color_current, glm::vec4 uv);

	void SetColor(const glm::vec3& color);

	const glm::vec3& GetColor() const;
	const glm::vec4& GetUV() const;

private:
	// Colors.
	glm::vec3 m_color_current;

	// Texture coordinates.
	glm::vec4 m_uv;
};
