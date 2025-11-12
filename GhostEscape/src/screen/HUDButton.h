#pragma once
#include "../affiliate/Sprite.h"
#include "../core/ObjectScreen.h"

class ButtonState;
class HUDButton:public ObjectScreen
{

protected:
    Sprite* sprite_normal_ = nullptr;
    Sprite* sprite_hover_ = nullptr;
    Sprite* sprite_press_ = nullptr;
    
    //按钮状态
    ButtonState* button_state_ = nullptr;
    
    bool is_trigger_ = false;
public:

    static HUDButton* addHUDButtonChild(Object* parent,
        const glm::vec2& position,
        const std::string& file_path1,
        const std::string& file_path2,
        const std::string& file_path3,
        float scale =1.f,
        Anchor anchor = Anchor::CENTER);
    
    void changeState(ButtonState* new_state);
    
    //set get
    Sprite* getSpriteNormal(){return sprite_normal_;}
    Sprite* getSpriteHover(){return sprite_hover_;}
    Sprite* getSpritePress(){return sprite_press_;}
    //trigger
    void setIsTrigger(bool is_trigger){is_trigger_ = is_trigger;}
    bool getIsTrigger();//只要触发一次就会重置trigger为false
    void setScale(float scale);
};
