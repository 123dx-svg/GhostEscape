#include "Effect.h"

#include "../core/Scene.h"


Effect* Effect::addEffectChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale,
    ObjectWorld* nextObject)
{
    Effect* effect = new Effect();
    effect->init();
    effect->setSprite(SpriteAnim::addSpriteAnimChild(effect, file_path,  scale));
    effect->sprite_->setLoop(false);
    effect->setPosition(pos);
    effect->setNextObject(nextObject);
    if (parent) parent->safeAddChild(effect);
    return effect;
}

void Effect::update(float deltaTime)
{
    ObjectWorld::update(deltaTime);
    checkFinish();
}

void Effect::clean()
{
    ObjectWorld::clean();
    if (nextObject_)
    {
        //保证nextObject_还没添加到容器中就清理  如果nextObject_已经添加到场景中就不该被删除 生命周期不归Effect管理
        nextObject_->clean();
        delete nextObject_;
        nextObject_ = nullptr;
    }
}

void Effect::checkFinish()
{
    if (sprite_ && sprite_->getFinish())
    {
        need_remove_ = true;
        if (nextObject_)
        {
            Game::getInstance().getCurrentScene()->safeAddChild(nextObject_);
            nextObject_ = nullptr;
        }
    }
}
