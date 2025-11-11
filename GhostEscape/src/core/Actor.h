#pragma once
#include "ObjectWorld.h"

class MoveControl;
class AffiliateBar;
class Stats;
class Actor : public ObjectWorld
{
protected:
    MoveControl* move_control_ = nullptr;
    Stats* stats_ = nullptr;//角色属性
    AffiliateBar* health_bar_ = nullptr;//血条
    glm::vec2 velocity_ = glm::vec2(0.f);//速度
    float max_speed_ = 100.f;//最大速度

public:

    void update(float deltaTime) override;
    
    void move(float deltaTime);
    void takeDamage(float damage) override;
    glm::vec2 getVelocity() const {return velocity_ ;}
    void setVelocity(const glm::vec2& velocity){velocity_ = velocity;}
    float getMaxSpeed() const {return max_speed_;}
    void setMaxSpeed(float max_speed){max_speed_ = max_speed;}
    Stats* getStats() { return stats_; }
    void setStats(Stats* stats) { stats_ = stats; }
    bool isAlive() const;
    AffiliateBar* getHealthBar() { return health_bar_; }
    void setHealthBar(AffiliateBar* health_bar) { health_bar_ = health_bar; }

    MoveControl* getMoveControl() { return move_control_; }
    void setMoveControl(MoveControl* move_control);//同一时刻只有一个移动控制
    void removeMoveControl();

private:
    void updateHealthBar();
};
