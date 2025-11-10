#pragma once
#include "../affiliate/Sprite.h"
#include "../core/Actor.h"
#include "../core/ObjectScreen.h"

class HUDStats :public ObjectScreen 
{

protected:
    class Actor* target_ = nullptr;
    Sprite* health_bar_ = nullptr;
    Sprite* health_bar_bg_ = nullptr;
    Sprite* health_icon_ = nullptr;
    Sprite* mana_bar_ = nullptr;
    Sprite* mana_bar_bg_ = nullptr;
    Sprite* mana_icon_ = nullptr;

    float health_percentage_ = 1.0f;
    float mana_percentage_ = 1.0f;

    //todo： 需要细致设置大小和偏移量
public:

    static HUDStats* addHUDStatsChild(Object* parent,Actor* target,glm::vec2 render_pos);
    
    void init() override;
    void update(float deltaTime) override;
    
    //set get
    void setHealthPercentage(float percentage){health_percentage_ = percentage;}
    float getHealthPercentage() const {return health_percentage_;}
    void setManaPercentage(float percentage){mana_percentage_ = percentage;}
    float getManaPercentage() const {return mana_percentage_;}
    void setHealthBar(Sprite* health_bar){health_bar_ = health_bar;}
    Sprite* getHealthBar() { return health_bar_; }
    void setHealthBarBG(Sprite* health_bar_bg){health_bar_bg_ = health_bar_bg;}
    Sprite* getHealthBarBG() { return health_bar_bg_; }
    void setHealthIcon(Sprite* health_icon){health_icon_ = health_icon;}
    Sprite* getHealthIcon() { return health_icon_; }
    void setManaBar(Sprite* mana_bar){mana_bar_ = mana_bar;}
    Sprite* getManaBar() { return mana_bar_; }
    void setManaBarBG(Sprite* mana_bar_bg){mana_bar_bg_ = mana_bar_bg;}
    Sprite* getManaBarBG() { return mana_bar_bg_; }
    void setManaIcon(Sprite* mana_icon){mana_icon_ = mana_icon;}
    Sprite* getManaIcon() { return mana_icon_; }
    void setTarget(class Actor* target){target_ = target;}
    class Actor* getTarget() const {return target_;}

private:
    void updateHealthBar();
    void updateManaBar();
};
