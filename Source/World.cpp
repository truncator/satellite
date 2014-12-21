#include "World.hpp"

#include "Entity.hpp"

World::World()
{
	for (int i = 0; i < 200; i++)
	{
		glm::vec2 position = glm::vec2(Random::Int(0, 1280), Random::Int(0, 720));
		glm::vec2 size = glm::vec2(32, 32);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);
		float rotation = Random::Float(0, 2 * 3.141592654);
		float rotation_velocity = Random::Float(-1.5f, 1.5f);
		glm::vec4 uv = glm::vec4(1, 1, 16, 16);

		m_entities.push_back(new Entity(position, size, velocity, acceleration, rotation, rotation_velocity, uv));
	}

	for (int i = 0; i < 5; i++)
	{
		glm::vec2 position = glm::vec2(Random::Int(0, 1280), Random::Int(0, 720));
		glm::vec2 size = glm::vec2(128, 128);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);
		float rotation = 0.0f;
		float rotation_velocity = 0.00f;
		glm::vec4 uv = glm::vec4(1, 18, 64, 64);

		m_entities.push_back(new Entity(position, size, velocity, acceleration, rotation, rotation_velocity, uv));
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

		/*
		if (Random::Int(0, 20) == 0)
			entity->Thrust();
			*/
	}
}

const std::vector<Entity*>& World::GetEntities() const
{
	return m_entities;
}
