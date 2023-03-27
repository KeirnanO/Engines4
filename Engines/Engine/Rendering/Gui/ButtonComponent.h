#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#include "SpriteSurface.h"
#include "GUIComponent.h"

class ButtonComponent : public GUIComponent
{
public:
    ButtonComponent();
    virtual ~ButtonComponent();

    virtual bool OnCreate(std::string imageName_, glm::vec2 guiOffset_, glm::vec2 guiScale_, float guiAngle_, glm::vec4 guiTint_) = 0;

    virtual void Draw(Camera* camera_, glm::vec2 position_)const;
    virtual void OnHit();

    SpriteSurface* sprite;
    SpriteSurface* unClickedSprite;
    SpriteSurface* clickedSprite;

private:
    glm::vec2 offset;
    bool isClicked;
    bool isClickable;
};


#endif // !BUTTONCOMPONENT_H