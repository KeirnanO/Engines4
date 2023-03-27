#include "GUIImageComponent.h"

GUIImageComponent::GUIImageComponent() {

}

GUIImageComponent::~GUIImageComponent() {
	delete sprite;
	sprite = nullptr;
}

bool GUIImageComponent::OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 guiScale_, float guiAngle_, glm::vec4 guiTint_) {
	sprite = new SpriteSurface(imageName_, guiScale_, guiAngle_, guiTint_);
	offset = offset_;
	return true;
}

void GUIImageComponent::Draw(Camera* camera_, glm::vec2 position_) {
	if (sprite) {
		sprite->DrawSurface(camera_, position_);
	}
}

void GUIImageComponent::OnClick() {
	
}