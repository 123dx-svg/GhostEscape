#include "Enemy.h"

#include "affiliate/AffiliateBar.h"
#include "core/Scene.h"
#include "raw/Stats.h"

Enemy* Enemy::addEnemyChild(Object* parent, glm::vec2 pos,Player* target)
{
    auto enemy_ = new Enemy();
    enemy_->init();
    enemy_->setPosition(pos);
    enemy_->setTarget(target);
    if (parent) parent->addChild(enemy_);
    return enemy_;
}

void Enemy::init()
{
    Actor::init();
   
    //添加动画
    anim_normal_ = SpriteAnim::addSpriteAnimChild(this,"Asset/sprite/ghost-Sheet.png",2.f);
    anim_hurt_ = SpriteAnim::addSpriteAnimChild(this,"Asset/sprite/ghostHurt-Sheet.png",2.f);
    anim_die_ = SpriteAnim::addSpriteAnimChild(this,"Asset/sprite/ghostDead-Sheet.png",2.f);
    anim_hurt_->setActive(false);
    anim_die_->setActive(false);
    anim_die_->setLoop(false);
    current_anim_ = anim_normal_;

    //添加碰撞组件
    collider_ = Collider::addColliderChild(this,current_anim_->getSize());
    //添加状态组件
    stats_ = Stats::addStatsChild(this);
    auto size = anim_normal_->getSize();
    //添加血条组件
    health_bar_ = AffiliateBar::addAffiliateBarChild(this,glm::vec2(size.x-10.f,10.f),Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset()+glm::vec2(0,size.y/2.f - 5.f));
    
    //设置敌人类别
    setType(ObjectType::ENEMY);

}

void Enemy::update(float deltaTime)
{
    //窗口外的敌人不更新
    auto render_pos_start = getRenderPosition() + current_anim_->getOffset();
    auto render_pos_end = render_pos_start + current_anim_->getOffset();
    if (!Game::getInstance().isRectCollideRect(render_pos_start,render_pos_end,glm::vec2(0),Game::getInstance().getScreenSize()))
        return;
    
    if (target_->getActive())
    {
        if (!move_control_)aim_target(target_);
        move(deltaTime);
        attack();
    }

    checkState();
    remove();
    
    Actor::update(deltaTime);
}

void Enemy::render()
{
    auto render_pos_start = getRenderPosition() + current_anim_->getOffset();
    auto render_pos_end = render_pos_start + current_anim_->getOffset();
    if (!Game::getInstance().isRectCollideRect(render_pos_start,render_pos_end,glm::vec2(0),Game::getInstance().getScreenSize()))
        return;
    Actor::render();
}

void Enemy::aim_target(Player* target)
{
    if (target == nullptr) return;
    auto direction = target->getPosition() - getPosition();
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::checkState()
{
    State new_state;
    if (stats_->getHealth() <= 0) new_state = State::Die;
    else if (stats_->getIsInvincible()) new_state = State::Hurt;
    else new_state = State::Normal;
    
    if (new_state != current_state_) changeState(new_state);

}

void Enemy::changeState(State new_state)
{

    current_anim_->setActive(false);
    
    switch (new_state) {
        case State::Normal:
            current_anim_ = anim_normal_;
            current_anim_->setActive(true);
            break;
        case State::Hurt:
            current_anim_ = anim_hurt_;
            current_anim_->setActive(true);
            break;
        case State::Die:
            current_anim_ = anim_die_;
            current_anim_->setActive(true);
            //敌人死亡时加分
            Game::getInstance().addScore(score_);
            break;
    }
    
    current_state_ = new_state;
}

void Enemy::attack()
{
    //确定自身和目标的碰撞组件
    if (!collider_||!target_||target_->getCollider()==nullptr) return;
    if (collider_->isColliding(target_->getCollider()))
    {
        //todo：攻击目标
        //判断属性是否存在
        if (stats_ && target_->getStats()!=nullptr)
        {
            target_->takeDamage(stats_->getDamage());
        }
    }
}

void Enemy::remove()
{
    if (anim_die_->getFinish())
    {
        setNeedRemove(true);
    }
}
