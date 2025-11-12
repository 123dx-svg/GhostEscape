#include "ButtonStateHover.h"

#include "ButtonStateNormal.h"
#include "ButtonStatePress.h"

void ButtonStateHover::onEnter()
{
   parent_->getSpriteHover()->setActive(true);
    Game::getInstance().playSound("Asset/sound/UI_button12.wav");
}

void ButtonStateHover::onExit()
{
    parent_->getSpriteHover()->setActive(false);
}

bool ButtonStateHover::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
        auto size = parent_->getSpriteNormal()->getSize();
        //鼠标离开区域
        if (!Game::getInstance().isMouseInRect(pos,pos+size))
        {
            parent_->changeState(new ButtonStateNormal());
            return true;
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button ==SDL_BUTTON_LEFT)
        {
            parent_->changeState(new ButtonStatePress());
            return true;
        }
        
    }
    
    return false;
}
