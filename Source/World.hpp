#pragma once

#include "Precompiled.hpp"

// Forward declarations.
class Entity;

//
// World
//     Manages the scene.
//

class World
{
public:
	World();
	~World();

	void Update(double dt);

	const std::vector<Entity*>& GetEntities() const;

private:
	std::vector<Entity*> m_entities;
};
