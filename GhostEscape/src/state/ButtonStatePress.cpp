#include "ButtonStatePress.h"

#include "ButtonStateNormal.h"

void ButtonStatePress::onEnter()
{
    parent_->getSpritePress()->setActive(true);
    Game::getInstance().playSound("Asset/sound/UI_button08.wav");
}

void ButtonStatePress::onExit()
{
    parent_->getSpritePress()->setActive(false);
}

bool ButtonStatePress::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        //左键松开
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
            auto size = parent_->getSpriteNormal()->getSize();
            //鼠标区域内
            if (Game::getInstance().isMouseInRect(pos,pos+size))
            {
                parent_->setIsTrigger(true);
            }
            parent_->changeState(new ButtonStateNormal());
            return true;
        }
        
    }
    return false;
}
