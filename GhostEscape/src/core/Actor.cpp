#include "Actor.h"

#include "Scene.h"
#include "../raw/Stats.h"
#include "../affiliate/AffiliateBar.h"

void Actor::update(float deltaTime)
{
    ObjectWorld::update(deltaTime);
    updateHealthBar();
}

void Actor::move(float deltaTime)
{
    setPosition(position_ + velocity_*deltaTime);
    //限制移动位置
    position_ = glm::clamp(position_,glm::vec2(0),Game::getInstance().getCurrentScene()->getWorldSize()-glm::vec2(20));
}

void Actor::takeDamage(float damage)
{
    if (stats_)
    {
        stats_->takeDamage(damage);
        
    }
}

bool Actor::isAlive() const
{
    if (stats_)
    {
        return stats_->getIsAlive();
    }
    return true;
}

void Actor::updateHealthBar()
{
    if (!stats_||!health_bar_) return;

    health_bar_->setPercentage(stats_->getHealth()/stats_->getMaxHealth());
}
