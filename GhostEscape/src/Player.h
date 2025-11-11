#pragma once
#include "WeaponThunder.h"
#include "affiliate/SpriteAnim.h"
#include "core/Actor.h"
#include "world/Effect.h"

class Timer;

class Player : public Actor
{
    
    
    WeaponThunder* weapon_thunder_ = nullptr;
    
    SpriteAnim* sprite_idle_ = nullptr;
    SpriteAnim* sprite_move_ = nullptr;//组合 生命周期归Player管理
    Effect* effect_ = nullptr; //聚合 生命周期不归Player管理
    Timer* flash_timer_ = nullptr;
    bool is_moving_ = false;
    
public:

    void init() override; //需要初始化的事物，在这里实现
    bool handleEvent(SDL_Event& event) override ;
    void update(float deltaTime) override ;
    void render() override ;
    void clean() override ;//需要清理的资源，在这里做

    void takeDamage(float damage) override;

    //自动逃离
    void autoEscape();
    void syncCamera();
    void checkState();
    void changeState(bool is_moving);
    void checkIsDead();
};


