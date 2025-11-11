#include "Spawner.h"

#include "Enemy.h"
#include "core/Scene.h"
#include "raw/MoveControl.h"

void Spawner::update(float deltaTime)
{
    Object::update(deltaTime);
    if (!target_||!target_->getActive()) return;
    timer_+=deltaTime;
    if (timer_>=interval_)
    {
        timer_=0.f;
        Game::getInstance().playSound("Asset/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < num_; ++i)
        {
            auto pos = Game::getInstance().randomVec2(Game::getInstance().getCurrentScene()->getCameraPosition(),Game::getInstance().getCurrentScene()->getCameraPosition()+Game::getInstance().getScreenSize() );
            Enemy* enemy_ = Enemy::addEnemyChild(nullptr,pos,target_);
            Effect::addEffectChild(Game::getInstance().getCurrentScene(),"Asset/effect/184_3.png",pos,1,enemy_);

            //测试代码转移控制权
            if (i==0)
            {
                enemy_->setMoveControl(new MoveControl());
                target_->removeMoveControl();
                
            }
        }
    }
}
