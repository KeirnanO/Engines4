#include "Transform.h"

Transform::Transform() : position(glm::vec3(0, 0, 0)), rotation(glm::vec3(0, 0, 0)), scale(glm::vec3(1, 1, 1))
{
}

Transform::Transform(glm::vec3 position_, glm::vec3 rotation_, glm::vec3 scale_)
{
	position = position_;
	rotation = rotation_;
	scale = scale_;
}

Transform::~Transform()
{
}

bool Transform::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void Transform::OnDestroy()
{
}

void Transform::Update(const float deltaTime_)
{
}

void Transform::Render() const
{
}
