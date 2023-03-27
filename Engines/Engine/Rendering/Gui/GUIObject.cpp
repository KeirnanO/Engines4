#include "GUIObject.h"

GUIObject::GUIObject(glm::vec2 position_, glm::vec2 scale_) {
	position = position_;
	scale = scale_;
}

GUIObject::~GUIObject() {

}

void GUIObject::Draw(Camera* camera_) {
	for (auto c : container) {
		c->Draw(camera_, position);
	}
}

void GUIObject::SetTag(std::string tag_) {
	tag = tag_;
}

void GUIObject::SetHit(bool hit_, int buttonType_) {
	hit = hit_;
	if (hit) {
		std::cout << tag << " was hit" << std::endl;
	}
}

glm::vec2 GUIObject::GetPosition()
{
	return position;
}

glm::vec2 GUIObject::GetScale()
{
	return scale;
}
