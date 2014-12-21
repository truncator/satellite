#include "Material.hpp"

Material::Material(glm::vec3 color_current, glm::vec4 uv) :
	m_color_current(color_current), m_uv(uv)
{
}

const glm::vec3& Material::GetColor() const
{
	return m_color_current;
}

const glm::vec4& Material::GetUV() const
{
	return m_uv;
}
