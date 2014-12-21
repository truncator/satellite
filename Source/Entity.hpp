#pragma once

#include "Precompiled.hpp"

#include "Transform.hpp"
#include "Graphics/Material.hpp"

//
// Entity
//     Base class for world objects.
//

class Entity
{
public:
	Entity(Transform transform, Material material);

	Transform& GetTransform();
	Material& GetMaterial();

private:
	Transform m_transform;
	Material m_material;

	// Physics.
	float m_mass;
};
