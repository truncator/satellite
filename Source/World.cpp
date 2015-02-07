#include "World.hpp"

#include "Entity.hpp"

World::World()
{
	for (int i = 0; i < 200; i++)
	{
		//glm::vec2 position = glm::vec2(Random::Int(0, 1280), Random::Int(0, 720));
		glm::vec2 position = 16.0f * glm::vec2(Random::Int(-640, 640), Random::Int(-360, 360));
		glm::vec2 size = glm::vec2(32, 32);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);
		float rotation = Random::Float(0, 2 * glm::pi<float>());
		float rotation_velocity = 0.0f;//Random::Float(-1.5f, 1.5f);
		float mass = 1.0f;
		glm::vec4 uv = glm::vec4(1, 1, 16, 16);

		glm::vec3 color = glm::vec3(0.8f, 0.8f, 0.8f);

		int primary_color = Random::Int(0, 3);
		if (primary_color == 0)
			color.x += Random::Float(0.1f, 0.2f);
		else if (primary_color == 1)
			color.y += Random::Float(0.1f, 0.2f);
		else
			color.z += Random::Float(0.1f, 0.2f);

		Transform transform = Transform(position, size, velocity, acceleration, rotation, rotation_velocity, mass);
		Material material = Material(color, uv);

		Entity* entity = new Entity(transform, material);
		m_entities.push_back(entity);
	}

	for (int i = 0; i < 25; i++)
	{
		//glm::vec2 position = glm::vec2(Random::Int(0, 1280), Random::Int(0, 720));
		glm::vec2 position = 16.0f * glm::vec2(Random::Int(-640, 640), Random::Int(-360, 360));
		glm::vec2 size = glm::vec2(128, 128);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);
		float rotation = -glm::pi<float>() / 2.0f;
		float rotation_velocity = 0.0f;
		float mass = 100.0f + Random::Float(0.0f, 20.0f);

		glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);

		int primary_color = Random::Int(0, 3);
		if (primary_color == 0)
			color.x += Random::Float(0.1f, 0.5f);
		else if (primary_color == 1)
			color.y += Random::Float(0.1f, 0.5f);
		else
			color.z += Random::Float(0.1f, 0.5f);

		glm::vec4 uv = glm::vec4(1, 18, 64, 64);

		Transform transform = Transform(position, size, velocity, acceleration, rotation, rotation_velocity, mass);
		Material material = Material(color, uv);

		Entity* entity = new Entity(transform, material);
		m_entities.push_back(entity);
		m_attractors.push_back(entity);
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
		entity->GetTransform().Update(dt);
		//entity->GetMaterial().Update(dt);

		if (entity->GetTransform().GetMass() < 0.01f)
		{
			#if 0
			if (Random::Int(0, 20) == 0)
				entity->GetTransform().Thrust();
			#endif
		}
	}
}

const std::vector<Entity*>& World::GetEntities() const
{
	return m_entities;
}

Entity* World::GetNearestAttractor(Entity* entity) const
{
	float max_attraction = -1.0f;
	Entity* nearest = nullptr;

	for (Entity* attractor : m_attractors)
	{
		// Don't attract itself.
		if (entity == attractor)
			continue;

		Transform& transform = attractor->GetTransform();
		glm::vec2 attractor_position = transform.GetPosition();
		float radius = transform.GetSize().x / 2.0f;
		float attraction = transform.GetAttraction();

		glm::vec2 entity_position = entity->GetTransform().GetPosition();

		float distance = glm::distance(attractor_position, entity_position) - radius;
		float net_attraction = attraction * (1.0f / (distance * distance));

		if (net_attraction > max_attraction)
		{
			max_attraction = net_attraction;
			nearest = attractor;
		}
	}

	return nearest;
}
