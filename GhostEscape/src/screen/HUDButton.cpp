#include "HUDButton.h"

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
    if (parent) parent->addChild(button);
    return button;
}

bool HUDButton::handleEvent(SDL_Event& event)
{
    ObjectScreen::handleEvent(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        //左键按下
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (is_hover_)
            {
                is_press_ = true;
                Game::getInstance().playSound("Asset/sound/UI_button08.wav");
                return true;
            }
        }
    }else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        //左键松开
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            is_press_ = false;
            if (is_hover_)//在范围内松开就是触发
            {
                is_trigger_ = true;
                return true;
            }
            
        }
    }
    return false;
}

void HUDButton::update(float deltaTime)
{
    ObjectScreen::update(deltaTime);
    checkHover();
    checkState();
}

void HUDButton::checkHover()
{
    bool new_hover_;
    auto pos = render_position + sprite_normal_->getOffset();
    auto size = sprite_normal_->getSize();
    if (Game::getInstance().isMouseInRect(pos,pos+size))
    {
        new_hover_ = true;
    }else
    {
        new_hover_ = false;
    }
    if (new_hover_!=is_hover_)
    {
        is_hover_ = new_hover_;
        if (is_hover_&&!is_press_) Game::getInstance().playSound("Asset/sound/UI_button12.wav");
    }
}

void HUDButton::checkState()
{
    if (!is_press_ && !is_hover_)
    {
        sprite_normal_->setActive(true);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(false);
    }else if (!is_press_&& is_hover_)
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(true);
        sprite_press_->setActive(false);
    }else
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(true);
    }
}

bool HUDButton::getIsTrigger()
{
    if (is_trigger_)
    {
        is_trigger_ = false;
        is_press_ = false;
        is_hover_ = false;
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
