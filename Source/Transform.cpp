#include "Transform.hpp"

Transform::Transform() :
	m_position(0.0f, 0.0f),
	m_size(1.0f, 1.0f),
	m_velocity(0.0f, 0.0f),
	m_acceleration(0.0f, 0.0f),
	m_rotation(0.0f),
	m_rotation_velocity(0.0f)
{
}

Transform::Transform(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity) :
	m_position(position),
	m_size(size),
	m_velocity(velocity),
	m_acceleration(acceleration),
	m_rotation(rotation),
	m_rotation_velocity(rotation_velocity)
{
}

void Transform::Update(double dt)
{
	m_velocity += m_acceleration * (float)dt;
	m_position += m_velocity * (float)dt;
	m_rotation += m_rotation_velocity * (float)dt;
}

void Transform::Thrust()
{
	float xd = glm::cos(m_rotation);
	float yd = glm::sin(m_rotation);
	glm::vec2 direction = glm::normalize(glm::vec2(xd, yd));

	m_acceleration = 5.0f * direction;
}

const glm::vec2& Transform::GetPosition() const
{
	return m_position;
}

const glm::vec2& Transform::GetSize() const
{
	return m_size;
}

const float Transform::GetRotation() const
{
	return m_rotation;
}
