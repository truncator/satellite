#pragma once

#include "Precompiled.hpp"

//
// Entity
//     Base class for world objects.
//

class Entity
{
public:
	Entity(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration);
	~Entity();

	void Update(double dt);

	void Thrust();

	const glm::vec2& GetPosition() const;
	const glm::vec2& GetSize() const;
	const float GetRotation() const;

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_rotation;
	float m_rotation_velocity;
};
