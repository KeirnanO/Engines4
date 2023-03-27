#include "ButtonComponent.h"
#include "../../Core/Engine.h"

ButtonComponent::ButtonComponent() {

}

ButtonComponent::~ButtonComponent() {
	delete sprite;
	sprite = nullptr;
}

bool ButtonComponent::OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 guiScale_, float guiAngle_, glm::vec4 guiTint_) {
	unClickedSprite = new SpriteSurface(imageName_, guiScale_, guiAngle_, guiTint_);
	clickedSprite = new SpriteSurface(imageName_, guiScale_, guiAngle_, guiTint_ / glm::vec4(10,10,10,1));

	sprite = unClickedSprite;
	offset = offset_;
	return true;
}

void ButtonComponent::Draw(Camera* camera_, glm::vec2 position_) const{
	if (sprite) {
		sprite->DrawSurface(camera_, position_);
	}
}


//Check if position is inside the bounds
void ButtonComponent::OnHit() {
	isClicked = true;
	sprite = clickedSprite;
}