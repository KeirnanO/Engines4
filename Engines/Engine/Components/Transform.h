#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform : public Component
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();
	Transform(glm::vec3 position_, glm::vec3 rotation_, glm::vec3 scale_);
	virtual ~Transform();
	virtual bool OnCreate(GameObject* parent_);
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
};

#endif // !TRANSFORM_H