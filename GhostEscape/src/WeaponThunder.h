#pragma once
#include "raw/Weapon.h"
#include "screen/HUDSkill.h"

class WeaponThunder:public Weapon
{

protected:
    HUDSkill* skill_hud_ = nullptr;
public:
    void init() override;
    void update(float deltaTime) override;
    
    static WeaponThunder* addWeaponThunderChild(Actor* parent,float cool_down,float mana_cost);
    bool handleEvent(SDL_Event& event) override;
};
