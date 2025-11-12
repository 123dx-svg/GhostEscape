#pragma once

#include "../core/Object.h"

class HUDSkill;
class Spell;
class Actor;

class Weapon : public Object
{

protected:
    Actor* parent_ = nullptr;
    Spell* spell_prototype_ = nullptr;//原型模式 攻击时复制Spell对象
    SDL_MouseButtonFlags trigger_button_ = SDL_BUTTON_LEFT; //应该单独封装个组件 目前只能鼠标
    HUDSkill* skill_hud_ = nullptr;
    std::string sound_path_ = "Asset/sound/big-thunder.mp3";
    
    float coolDown_ = 1.f;
    float manaCost_ = 1.f;
    float coolDownTimer_ = 0.f;

    
public:
    static Weapon* addWeaponChild(Actor* parent,float cool_down,float mana_cost);
    
    void update(float deltaTime) override;
    bool handleEvent(SDL_Event& event) override;
    void attack(glm::vec2 pos);
    bool canAttack();//判断是否可以攻击

    
    //get set
    void setCoolDown(float coolDown) { coolDown_ = coolDown; }
    float getCoolDown() { return coolDown_; }
    void setManaCost(float manaCost) { manaCost_ = manaCost; }
    float getManaCost() { return manaCost_; }
    void setParent(Actor* parent) { parent_ = parent; }
    Actor* getParent() { return parent_; }
    
    void setSpellPrototype(Spell* spell_prototype) { spell_prototype_ = spell_prototype; }
    Spell* getSpellPrototype() { return spell_prototype_; }
    void setTriggerButton(SDL_MouseButtonFlags trigger_button) { trigger_button_ = trigger_button; }
    SDL_MouseButtonFlags getTriggerButton() { return trigger_button_; }
    void setSkillHUD(HUDSkill* skill_hud) { skill_hud_ = skill_hud; }
    HUDSkill* getSkillHUD() { return skill_hud_; }
    void setSoundPath(std::string sound_path) { sound_path_ = sound_path; }
    
    
    
    
    
    
};
