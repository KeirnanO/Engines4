#include "Rigidbody.h"

Rigidbody::Rigidbody() : angle(0), mass(1), linearvelocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)) 
{
}

Rigidbody::~Rigidbody()
{

}

bool Rigidbody::OnCreate(GameObject* parent_)
{
	parent = parent_;
	position = parent->GetPosition();
	position_last = parent->GetPosition();
	return true;
}

void Rigidbody::OnDestroy()
{

}

void Rigidbody::Update(const float dt)
{
	// Compute how much we moved
	const glm::vec3 displacement = position - position_last;
	// Update position
	position_last = position;

	//Accelerate(glm::vec3(0.0f, 10.0f, 0.0f));

	position = position + displacement + acceleration * (dt * dt);
	// Reset acceleration
	acceleration = {};

	
	parent->SetPosition(position);
}

void Rigidbody::Render() const
{
}

void Rigidbody::UpdatePositions(const float deltaTime_) {
	position += linearvelocity * deltaTime_;
}

void Rigidbody::Accelerate(glm::vec3 acceleration_)
{
	acceleration += acceleration_;
}

void Rigidbody::AddForce(glm::vec3 force)
{
	linearvelocity += force;
	position += force;
}

void Rigidbody::setVelocity(glm::vec3 velocity, float dt)
{
	position_last = position - (velocity * dt);
}
