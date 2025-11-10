#pragma once
#include "Player.h"
#include "core/Actor.h"


class Enemy:public Actor
{
    enum class State {
        Normal,
        Hurt,
        Die,
    };


    State current_state_ = State::Normal;
    Player* target_ = nullptr;
    //目标敌人状态
    SpriteAnim* anim_normal_ = nullptr;
    SpriteAnim* anim_hurt_ = nullptr;
    SpriteAnim* anim_die_ = nullptr;

    SpriteAnim* current_anim_ = nullptr;

    //价值分数
    int score_ = 10;
public:

    static Enemy* addEnemyChild(Object* parent,glm::vec2 pos,Player* target);
    
    void init() override;
    void update(float deltaTime) override;
    
    void aim_target(Player* target);

    void checkState();
    void changeState(State new_state);
    void attack();
    void remove();

    //get set
    Player* getTarget() const {return target_;}
    void setTarget(Player* target){target_ = target;}
};
