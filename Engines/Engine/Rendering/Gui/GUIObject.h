#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <glew.h>
#include <glm/glm.hpp>
#include <string>
#include "GUIComponent.h"
#include "../../Core/Debug.h"

class GUIObject
{
public:

	GUIObject(glm::vec2 position_, glm::vec2 scale_);
	~GUIObject();

	void Draw(Camera* camera_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);
	glm::vec2 GetPosition();
	glm::vec2 GetScale();

	template<typename T>
	void AddComponent() {
		T* temp = new T();
		if (dynamic_cast<GUIComponent*>(temp)) {
			if (GetComponent<T>()) {
				Debug::Error("Failed to add already existing component. Deleting Components", "GameObject.cpp", __LINE__);
				delete temp;
				temp = nullptr;
				return;
			}
			else if (GetComponent<T>() == nullptr) {
				container.push_back(temp);
			}
		}

		else {
			Debug::Error("Object is not a child of component. Deleting Components", "GameObject.cpp", __LINE__);
			delete temp;
			temp = nullptr;
			return;
		}
	}

	template<typename D>
	D* GetComponent() {
		for (auto c : container) {
			if (dynamic_cast<D*>(c)) {
				return dynamic_cast<D*>(c);
			}
		}
		return nullptr;
	}

	template<typename E>
	void RemoveComponent() {
		for (int i = 0; i < container.size(); i++) {
			if (dynamic_cast<E*>(container[i])) {
				delete container[i];
				container[i] = nullptr;
				container.erase(container.begin() + i); // Always delete before you remove
			}
		}
	}

	


private:
	std::vector<GUIComponent*> container;
	glm::vec2 position;
	glm::vec2 scale;
	std::string tag;
	bool hit;

};

#endif