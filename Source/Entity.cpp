#include "Entity.hpp"

Entity::Entity(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity, glm::vec4 uv) :
	m_position(position),
	m_size(size),
	m_velocity(velocity),
	m_acceleration(acceleration),
	m_rotation(rotation),
	m_rotation_velocity(rotation_velocity),
	m_uv(uv)
{
}

Entity::~Entity()
{
}

void Entity::Update(double dt)
{
	m_velocity += m_acceleration * (float)dt;
	m_position += m_velocity * (float)dt;
	m_rotation += m_rotation_velocity * (float)dt;
}

void Entity::Thrust()
{
	float xd = glm::cos(m_rotation);
	float yd = glm::sin(m_rotation);
	glm::vec2 direction = glm::normalize(glm::vec2(xd, yd));

	m_acceleration = 5.0f * direction;
}

const glm::vec2& Entity::GetPosition() const
{
	return m_position;
}

const glm::vec2& Entity::GetSize() const
{
	return m_size;
}

const float Entity::GetRotation() const
{
	return m_rotation;
}

const glm::vec4& Entity::GetUV() const
{
	return m_uv;
}
