#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include "SpriteSurface.h"
#include "GUIComponent.h"

class GUIImageComponent : public GUIComponent
{
public:
    GUIImageComponent();
    virtual ~GUIImageComponent();

    virtual bool OnCreate(std::string imageName_, glm::vec2 offset_ = glm::vec2(0.0f, 0.0f), glm::vec2 scale_ = glm::vec2(1.0f, 1.0f), float angle_ = 0.0f, glm::vec4 tint_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) override;

    virtual void Draw(Camera* camera_, glm::vec2 position_);

    virtual void OnClick();

private:

    SpriteSurface* sprite;
    glm::vec2 offset;

};


#endif // !GUIIMAGECOMPONENT_H