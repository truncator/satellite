#include "Transform.hpp"

Transform::Transform() :
	m_position(0.0f, 0.0f),
	m_size(1.0f, 1.0f),
	m_velocity(0.0f, 0.0f),
	m_acceleration(0.0f, 0.0f),
	m_rotation(0.0f),
	m_rotation_velocity(0.0f),
	m_mass(0.0f),
	m_forces(0.0f)
{
}

Transform::Transform(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity, float mass) :
	m_position(position),
	m_size(size),
	m_velocity(velocity),
	m_acceleration(acceleration),
	m_rotation(rotation),
	m_rotation_velocity(rotation_velocity),
	m_mass(mass),
	m_forces(0.0f)
{
}

void Transform::Update(double dt)
{
	// Verlet integration based on
	// http://gamedev.stackexchange.com/a/41917
	
	// Calculate acceleration.
	m_acceleration = (m_forces / m_mass);

	m_position += (m_velocity + (float)dt * m_acceleration / 2.0f) * (float)dt;
	m_velocity += m_acceleration * (float)dt;

	// Adjust the velocity by the new acceleration.
	glm::vec2 new_acceleration = m_forces / m_mass;
	m_velocity += ((new_acceleration - m_acceleration) / 2.0f) * (float)dt;

	m_rotation += m_rotation_velocity * (float)dt;

	// Reset forces.
	m_forces = glm::vec2(0.0f, 0.0f);
}

void Transform::Thrust()
{
	float xd = glm::cos(m_rotation);
	float yd = glm::sin(m_rotation);
	glm::vec2 direction = glm::normalize(glm::vec2(xd, yd));

	m_forces += 5.0f * direction;
}

void Transform::Attract(Transform& transform, double dt)
{
	glm::vec2 direction = glm::normalize(m_position - transform.GetPosition());
	glm::vec2 force = direction * GetAttraction();
	transform.ApplyForce(force, dt);
}

void Transform::ApplyForce(const glm::vec2& force, double dt)
{
	m_forces += force;
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

const float Transform::GetMass() const
{
	return m_mass;
}

const float Transform::GetAttraction() const
{
	return glm::sqrt(m_mass * 0.01f);
}
