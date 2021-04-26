#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	float GetAngle() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);
	void SetTag(std::string tag_); //<<<<<<<<<<<<<<<--------------------------------------------------------------
	void SetHit(bool hit_, int buttonType_); // something i would do - but seems like the object shouldnt handle this

private:
	Model* model;
	unsigned int modelInstance;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;
	std::string tag;

	BoundingBox boundingBox;

	bool hit;
};

#endif // !GAMEOBJECT_H