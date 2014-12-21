#pragma once

#include "Precompiled.hpp"

//
// Transform
//

class Transform
{
public:
	Transform();
	Transform(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity);

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
