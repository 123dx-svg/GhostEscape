#pragma once
#include "../core/Actor.h"
#include "../core/Object.h"

/*战斗属性*/
class Stats:public Object
{
protected:
    Actor* parent_ = nullptr;
    float health_ = 100.f;
    float max_health_ = 100.f;
    float mana_ =  100.f;
    float max_mana_ = 100.f;
    float damage_ =40.f;
    float mana_regen_ = 10.f;

    bool is_alive_ = true;
    //无敌时间
    bool is_invincible_ = false;
    float invincible_time_ = 1.5f;
    float invincible_timer_ = 0.f;

public:
    static Stats* addStatsChild(Actor* parent, float max_health=100.f, float max_mana=100.f, float damage=40.f, float mana_regen=10.f);
    
    void update(float deltaTime) override;
    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);

    //自动回复蓝量
    void autoRegenMana(float deltaTime);
    void takeDamage(float damage);
    //get set
    float getHealth() { return health_; }
    float getMaxHealth() { return max_health_; }
    void setHealth(float health) { health_ = health; }
    void setMaxHealth(float max_health) { max_health_ = max_health; }
    float getMana() { return mana_; }
    void setMana(float mana) { mana_ = mana; }
    void setMaxMana(float max_mana) { max_mana_ = max_mana; }
    float getMaxMana() { return max_mana_; }
    float getDamage() { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    float getManaRegen() { return mana_regen_; }
    void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
    bool getIsAlive() { return is_alive_; }
    void setAlive(bool alive) { is_alive_ = alive; }
    void setParent(Actor* parent) { parent_ = parent; }
    Actor* getParent() { return parent_; }
    bool getIsInvincible() { return is_invincible_; }
    void setInvincible(bool invincible) { is_invincible_ = invincible; }
    float getInvincibleTime() { return invincible_time_; }
    void setInvincibleTime(float invincible_time) { invincible_time_ = invincible_time; }
    
};
