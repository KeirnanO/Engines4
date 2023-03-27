#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"

class Rigidbody : public Component 
{
private:
	
	uint16_t angle;	
	glm::vec3 linearvelocity;
	glm::vec3 angularvelocity;
	glm::vec3 acceleration;
	
public:
	Rigidbody();
	virtual ~Rigidbody();
	virtual bool OnCreate(GameObject* parent_);
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	void UpdatePositions(const float deltaTime_);
	void Accelerate(glm::vec3 acceleration_);
	void AddForce(glm::vec3 Force);
	void setVelocity(glm::vec3 velocity, float dt);
	float getRadius() {
		return 1.0f;
	}
	glm::vec3 position;
	glm::vec3 position_last;
	bool isKinematic = true;
	float mass = 1;
};



#endif // !RIGIDBODY_H
