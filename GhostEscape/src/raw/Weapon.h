#pragma once

#include "../core/Object.h"

class Spell;
class Actor;

class Weapon : public Object
{

protected:
    Actor* parent_ = nullptr;
    float coolDown_ = 1.f;
    float manaCost_ = 1.f;
    float coolDownTimer_ = 0.f;

    
public:
    void update(float deltaTime) override;


    void attack(glm::vec2 pos, Spell* spell);//确保调用attack
    bool canAttack();//判断是否可以攻击

    
    //get set
    void setCoolDown(float coolDown) { coolDown_ = coolDown; }
    float getCoolDown() { return coolDown_; }
    void setManaCost(float manaCost) { manaCost_ = manaCost; }
    float getManaCost() { return manaCost_; }
    void setParent(Actor* parent) { parent_ = parent; }
    Actor* getParent() { return parent_; }
    
    
    
};
