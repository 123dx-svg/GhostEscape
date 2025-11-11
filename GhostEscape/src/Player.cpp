#include "Player.h"

#include "affiliate/SpriteAnim.h"
#include "affiliate/TextLabel.h"
#include "core/Scene.h"
#include "raw/MoveControl.h"
#include "raw/Stats.h"
#include "raw/Timer.h"

void Player::init()
{
    Actor::init();
    //闪烁频率
    flash_timer_ = Timer::addTimerChild(this,0.4f);
    flash_timer_->start();
    max_speed_ = 500.f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this,"Asset/sprite/ghost-idle.png",2.f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this,"Asset/sprite/ghost-move.png",2.f);
    sprite_move_->setActive(false);

    //添加碰撞组件
    collider_ = Collider::addColliderChild(this,sprite_idle_->getSize()/2.0f);
    //添加状态组件
    stats_ = Stats::addStatsChild(this);
    //添加特效组件 归为场景管理
    effect_ = Effect::addEffectChild(Game::getInstance().getCurrentScene(),"Asset/effect/1764.png",glm::vec2(0),2.f);
    effect_->setActive(false);
    //创建武器
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this,2.f,40.f);

    setMoveControl(new MoveControl());
}

bool Player::handleEvent(SDL_Event& event)
{
    Actor::handleEvent(event);
    if (weapon_thunder_->handleEvent(event)) return true;
    return false;
}
void Player::update(float deltaTime)
{
    Actor::update(deltaTime);
    if (!move_control_) autoEscape();
    checkState();
    move(deltaTime);
    syncCamera();
    checkIsDead();
}

void Player::render()
{
    if (stats_->getIsInvincible()&&flash_timer_->getProgress()<0.5) return;
    Actor::render();
   //Game::getInstance().drawBoundary(render_position,render_position+glm::vec2(20,20),5,{1,0,0,1});
}

void Player::clean()
{
    Actor::clean();
}

void Player::takeDamage(float damage)
{
    if (!stats_||stats_->getIsInvincible()) return;
    Actor::takeDamage(damage);
    Game::getInstance().playSound("Asset/sound/hit-flesh-02-266309.mp3");
}

void Player::autoEscape()
{
    //todo:自动逃离
    velocity_ = glm::vec2(0,0);
}


void Player::syncCamera()
{
    Game::getInstance().getCurrentScene()->setCameraPosition(position_-Game::getInstance().getScreenSize()/2.f);
}

void Player::checkState()
{
    
    
    //方向判断
    if (velocity_.x<0)
    {
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }
    else
    {
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }
    //判断运动状态是否切换
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_)
    {
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
   
}

void Player::changeState(bool is_moving)
{
    if (is_moving)
    {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        //同步当前帧和时间 让动画更加丝滑
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    }
    else
    {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsDead()
{
    if (!stats_->getIsAlive())
    {
        //添加死亡特效
        effect_->setActive(true);
        effect_->setPosition(getPosition());
        //setNeedRemove(true);这里移除后Enemy那边player指针依旧会是野指针
        setActive(false);
        Game::getInstance().playSound("Asset/sound/female-scream-02-89290.mp3");
    }
}
