#include "Spell.h"

#include "../core/Scene.h"

Spell* Spell::addSpellChild(Object* parent, const std::string& file_path, glm::vec2 pos, float damage, float scale, Anchor anchor)
{
    auto spell = new Spell();
    spell->file_path_ = file_path;
    spell->scale_ = scale;
    spell->init();
    spell->damage_ = damage;
    spell->sprite_ = SpriteAnim::addSpriteAnimChild(spell, file_path, scale, anchor);
    auto size = spell->sprite_->getSize();
    spell->collider_ = Collider::addColliderChild(spell, size,Collider::Type::Circle,anchor);
    spell->sprite_->setLoop(false);
    spell->setPosition(pos);
    if (parent) parent->safeAddChild(spell);
    
    return spell;
}

Spell* Spell::clone()
{
    return addSpellChild(Game::getInstance().getCurrentScene(),file_path_,
        getPosition(),damage_,scale_,sprite_->getAnchor());
}

void Spell::update(float deltaTime)
{
    ObjectWorld::update(deltaTime);

    //检测是否播放完成
    if (sprite_->getFinish()) need_remove_ = true;
    attack();
    
}

void Spell::attack()
{
    auto objects = Game::getInstance().getCurrentScene()->getChildrenWorld();
    for (auto& object : objects)
    {
        if (object->getType() != ObjectType::ENEMY) continue;

        if (collider_&& object->getCollider()&&collider_->isColliding(object->getCollider()))
        {
            object->takeDamage(damage_);
        }
    }
}
