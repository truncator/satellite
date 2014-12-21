#include "Entity.hpp"

Entity::Entity(Transform transform, Material material) :
	m_transform(transform), m_material(material)
{
}

Transform& Entity::GetTransform()
{
	return m_transform;
}

Material& Entity::GetMaterial()
{
	return m_material;
}
