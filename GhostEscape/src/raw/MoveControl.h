#pragma once
#include "../core/Object.h"


class Actor;
class MoveControl : public Object
{

protected:
    bool is_up_ = false;
    bool is_down_ = false;
    bool is_left_ = false;
    bool is_right_ = false;
    Actor* parent_ = nullptr;
    float max_speed_ = 500.f;
public:
    void update(float deltaTime) override;
    // void checkInput();
    bool handleEvent(SDL_Event& event) override;

    
    //getter
    bool getIsUp() const {return is_up_;}
    bool getIsDown() const {return is_down_;}
    bool getIsLeft() const {return is_left_;}
    bool getIsRight() const {return is_right_;}
    void setParent(Actor* actor){parent_ = actor;}
    Actor* getParent() const {return parent_;}
    float getMaxSpeed() const {return max_speed_;}
    void setMaxSpeed(float speed){max_speed_ = speed;}
};
