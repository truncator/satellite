#pragma once

#include "Precompiled.hpp"

//
// Entity
//     Base class for world objects.
//

class Entity
{
public:
	Entity(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity, glm::vec4 uv);
	~Entity();

	void Update(double dt);

	void Thrust();

	const glm::vec2& GetPosition() const;
	const glm::vec2& GetSize() const;
	const float GetRotation() const;
	const glm::vec4& GetUV() const;

private:
	// Transform
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_rotation;
	float m_rotation_velocity;

	// Physics
	float m_mass;

	// Render
	glm::vec4 m_uv;
};
