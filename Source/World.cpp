#include "World.hpp"

#include "Entity.hpp"

World::World()
{
	for (int i = 0; i < 50; i++)
	{
		glm::vec2 position = glm::vec2(Random::Int(0, 640), Random::Int(0, 480));
		glm::vec2 size = glm::vec2(32, 32);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);

		m_entities.push_back(new Entity(position, size, velocity, acceleration));
	}
}

World::~World()
{
	for (int i = 0; i < m_entities.size(); i++)
		delete m_entities[i];

	m_entities.clear();
}

void World::Update(double dt)
{
	for (Entity* entity : m_entities)
	{
		entity->Update(dt);

		if (Random::Int(0, 20) == 0)
			entity->Thrust();
	}
}

const std::vector<Entity*>& World::GetEntities() const
{
	return m_entities;
}
