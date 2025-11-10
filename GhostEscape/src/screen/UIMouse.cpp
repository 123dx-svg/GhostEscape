#include "UIMouse.h"
#include "../affiliate/Sprite.h"
void UIMouse::update(float deltaTime)
{
    ObjectScreen::update(deltaTime);
    timer_ += deltaTime;
    if (timer_<0.3f)
    {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
        
    }
    else if (timer_<0.6f)
    {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    }
    else
    {
        timer_ = 0.0f;
    }
    setRenderPosition(Game::getInstance().getMousePos());
}

UIMouse* UIMouse::addUIMouse(Object* parent, const std::string& path1, const std::string& path2, float scale,
    Anchor anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->sprite1_ = Sprite::addSpriteChild(ui_mouse,path1,scale,anchor);
    ui_mouse->sprite2_ = Sprite::addSpriteChild(ui_mouse,path2,scale,anchor);
    if (parent)parent->addChild(ui_mouse);
    return ui_mouse;
}
