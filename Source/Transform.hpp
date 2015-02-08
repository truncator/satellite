#pragma once

#include "Precompiled.hpp"

//
// Transform
//

class Transform
{
public:
	Transform();
	Transform(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, glm::vec2 acceleration, float rotation, float rotation_velocity, float mass);

	void Update(double dt);

	void Thrust();
	void Attract(Transform& transform, double dt);
	void ApplyForce(const glm::vec2& force, double dt);

	void SetStatic(bool _static);

	const glm::vec2& GetPosition() const;
	const glm::vec2& GetSize() const;
	const float GetRotation() const;
	const float GetMass() const;
	const float GetAttraction() const;
	bool IsStatic() const;

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_rotation;
	float m_rotation_velocity;
	float m_mass;

	bool m_static;

	// Accumulated per-frame forces.
	glm::vec2 m_forces;
};
