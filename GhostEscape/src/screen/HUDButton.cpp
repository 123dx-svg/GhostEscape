#include "HUDButton.h"

#include "../state/ButtonState.h"
#include "../state/ButtonStateNormal.h"

HUDButton* HUDButton::addHUDButtonChild(Object* parent,const glm::vec2& position, const std::string& file_path1,
                                        const std::string& file_path2, const std::string& file_path3, float scale, Anchor anchor)
{
    auto button = new HUDButton();
    button->init();
    button->setRenderPosition(position);
    button->sprite_normal_ = Sprite::addSpriteChild(button, file_path1, scale, anchor);
    button->sprite_hover_ = Sprite::addSpriteChild(button, file_path2, scale, anchor);
    button->sprite_press_ = Sprite::addSpriteChild(button, file_path3, scale, anchor);
    button->sprite_hover_->setActive(false);
    button->sprite_press_->setActive(false);
    button->changeState(new ButtonStateNormal());
    if (parent) parent->addChild(button);
    return button;
}

void HUDButton::changeState(ButtonState* new_state)
{
    //旧状态退出
       if (button_state_)
       {
           button_state_->onExit();
           button_state_->setNeedRemove(true);
       }
    //新状态进入
    if (new_state)
    {
        button_state_ = new_state;
        button_state_->init();
        //这个先后顺序不能反
        new_state->setParent(this);
        new_state->onEnter();
        //自动管理生命周期
        safeAddChild(button_state_);
    }
}

bool HUDButton::getIsTrigger()
{
    if (is_trigger_)
    {
        is_trigger_ = false;
        return true;
    }
    return false;
}

void HUDButton::setScale(float scale)
{
    sprite_normal_->setScale(scale);
    sprite_hover_->setScale(scale);
    sprite_press_->setScale(scale);
}
