#pragma once
#include "../affiliate/Sprite.h"
#include "../core/ObjectScreen.h"

class HUDButton:public ObjectScreen
{

protected:
    Sprite* sprite_normal_ = nullptr;
    Sprite* sprite_hover_ = nullptr;
    Sprite* sprite_press_ = nullptr;
    bool is_hover_ = false;
    bool is_press_ = false;
    bool is_trigger_ = false;
public:

    static HUDButton* addHUDButtonChild(Object* parent,
        const glm::vec2& position,
        const std::string& file_path1,
        const std::string& file_path2,
        const std::string& file_path3,
        float scale =1.f,
        Anchor anchor = Anchor::CENTER);

    bool handleEvent(SDL_Event& event) override;
    void update(float deltaTime) override;
    void checkHover();
    void checkState();
    
    //set get
    Sprite* getSpriteNormal(){return sprite_normal_;}
    Sprite* getSpriteHover(){return sprite_hover_;}
    Sprite* getSpritePress(){return sprite_press_;}
    //hover press trigger
    void setIsHover(bool is_hover){is_hover_ = is_hover;}
    bool getIsHover(){return is_hover_;}
    void setIsPress(bool is_press){is_press_ = is_press;}
    bool getIsPress(){return is_press_;}
    void setIsTrigger(bool is_trigger){is_trigger_ = is_trigger;}
    bool getIsTrigger();//只要触发一次就会重置trigger为false
    void setScale(float scale);
};
