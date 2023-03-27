#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Rendering/3D/GameObject.h"

class GameObject;
class Component {
public:
	inline Component() : parent(nullptr) {}
	virtual ~Component() { parent = nullptr; }
	virtual bool OnCreate(GameObject* parent_) = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render()const = 0;
protected:
	GameObject* parent;

};


#endif