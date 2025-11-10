#include "Stats.h"

Stats* Stats::addStatsChild(Actor* parent, float max_health, float max_mana, float damage, float mana_regen)
{
    Stats* stats = new Stats();
    stats->setParent(parent);
    stats->setHealth(max_health);
    stats->setMaxHealth(max_health);
    stats->setMana(max_mana);
    stats->setMaxMana(max_mana);
    stats->setDamage(damage);
    stats->setManaRegen(mana_regen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float deltaTime)
{
    Object::update(deltaTime);
    autoRegenMana(deltaTime);
    //计算无敌时间
    if (is_invincible_)
    {
        invincible_timer_ += deltaTime;
        if (invincible_timer_ >= invincible_time_)
        {
            is_invincible_ = false;
            invincible_timer_ = 0.f;
        }   
    }
}

bool Stats::canUseMana(float mana_cost)
{
    return mana_ >= mana_cost;
}

void Stats::useMana(float mana_cost)
{
    mana_ = mana_cost;
    if (mana_ <= 0)
    {
        mana_ = 0;
    }
}

void Stats::autoRegenMana(float deltaTime)
{
    mana_ += mana_regen_ * deltaTime;
    mana_ = std::min(mana_, max_mana_);
}

void Stats::takeDamage(float damage)
{
    if (is_invincible_)return;

    health_ -= damage;
    
    if (health_ <= 0)
    {
        health_ = 0;
        is_alive_ = false;
    }
    //SDL_Log("Actor health: %f", health_);
    is_invincible_ = true;
    invincible_timer_ = 0.f;
}
