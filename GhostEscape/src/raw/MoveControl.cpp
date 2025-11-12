#include "MoveControl.h"

#include "../core/Actor.h"

void MoveControl::update(float deltaTime)
{
    Object::update(deltaTime);
    if (parent_ == nullptr) return;
    parent_->setVelocity(parent_->getVelocity()*0.9f);
    auto direction = glm::vec2(is_right_ - is_left_, is_down_ - is_up_);
    if (glm::length(direction)>0.1f)
    {
        direction = glm::normalize(direction);
        //速度为0时不立即停止
        parent_->setVelocity(direction*max_speed_);
    }
    
}

bool MoveControl::handleEvent(SDL_Event& event)
{
    
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.scancode == SDL_SCANCODE_W) is_up_ = true;
        else if (event.key.scancode == SDL_SCANCODE_S) is_down_ = true;
        else if (event.key.scancode == SDL_SCANCODE_A) is_left_ = true;
        else if (event.key.scancode == SDL_SCANCODE_D) is_right_ = true;
        return true;
    }
    if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.scancode == SDL_SCANCODE_W) is_up_ = false;
        else if (event.key.scancode == SDL_SCANCODE_S) is_down_ = false;
        else if (event.key.scancode == SDL_SCANCODE_A) is_left_ = false;
        else if (event.key.scancode == SDL_SCANCODE_D) is_right_ = false;
        return true;
    }
    
    
    return Object::handleEvent(event);
}

// void MoveControl::checkInput()
// {
//     auto keyboard = SDL_GetKeyboardState(NULL);
//     is_up_     = keyboard[SDL_SCANCODE_W];
//     is_down_   = keyboard[SDL_SCANCODE_S];
//     is_left_   = keyboard[SDL_SCANCODE_A];
//     is_right_  = keyboard[SDL_SCANCODE_D];
// }
