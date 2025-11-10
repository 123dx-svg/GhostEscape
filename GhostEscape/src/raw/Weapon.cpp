#include "Weapon.h"

#include "Stats.h"
#include "../core/Actor.h"
#include "../core/Scene.h"
#include "../world/Spell.h"

void Weapon::update(float deltaTime)
{
    Object::update(deltaTime);
    coolDownTimer_ += deltaTime;

}

void Weapon::attack(glm::vec2 pos, Spell* spell)
{
    if (spell == nullptr) return;

    parent_->getStats()->useMana(manaCost_);
    coolDownTimer_ = 0.0f;
    spell->setPosition(pos);
    Game::getInstance().getCurrentScene()->safeAddChild(spell);

}

bool Weapon::canAttack()
{
    if (coolDownTimer_ < coolDown_) return false;
    if (!parent_->getStats()->canUseMana(manaCost_)) return false;
    return true;
}
