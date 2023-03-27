#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Components/Component.h"

class Component;
class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);


	//Adding Components To a GameObject
	template<typename ComponentTemplate, typename ... Args>
	ComponentTemplate* AddComponent(Args&& ... args_) {
		ComponentTemplate* comp = new ComponentTemplate(std::forward<Args>(args_)...);
		if (!dynamic_cast<Component*>(comp)) {
			///Trying to add a component that is not a base class of Component class
			delete comp;
			comp = nullptr;
			return nullptr;
		}
		if (GetComponent<ComponentTemplate>()) {
			///Trying to add a component type that is already added
			delete comp;
			comp = nullptr;
			return nullptr;
		}
		components.push_back(comp);
		comp->OnCreate(this);
		return dynamic_cast<ComponentTemplate*>(comp);
	}

	template<typename ComponentTemplate>
	ComponentTemplate* GetComponent() {
		for (auto component : components) {
			if (dynamic_cast<ComponentTemplate*>(component)) {
				return dynamic_cast<ComponentTemplate*>(component);
			}
		}
		return nullptr;
	}

	template<typename ComponentTemplate>
	void RemoveComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (dynamic_cast<ComponentTemplate*>(components[i])) {
				delete components[i];
				components[i] = nullptr;
				components.erase(components.begin() + i);
				break;
			}
		}
	}



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
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

private:
	Model* model;
	unsigned int modelInstance;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;
	std::string tag;

	BoundingBox boundingBox;
	std::vector<Component*> components;

	bool hit;
};

#endif // !GAMEOBJECT_H