#include "Weapon.h"

#include "Stats.h"
#include "../core/Actor.h"
#include "../core/Scene.h"
#include "../world/Spell.h"
#include "../screen/HUDSkill.h"

Weapon* Weapon::addWeaponChild(Actor* parent, float cool_down, float mana_cost)
{
    Weapon* weapon = new Weapon();
    weapon->setParent(parent);
    weapon->coolDown_ = cool_down;
    weapon->manaCost_ = mana_cost;
    if (parent)parent->safeAddChild(weapon);
    return weapon;
}

void Weapon::update(float deltaTime)
{
    Object::update(deltaTime);
    coolDownTimer_ += deltaTime;
    if (skill_hud_) skill_hud_->setPercentage(coolDownTimer_/coolDown_);//更新技能图标
}

bool Weapon::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == trigger_button_)
        {
             attack(Game::getInstance().getMousePos()+Game::getInstance().getCurrentScene()->getCameraPosition());
            
             return true;
            
        }
    }
    return Object::handleEvent(event);
}

void Weapon::attack(glm::vec2 pos)
{
    if (spell_creator_ == nullptr||!canAttack()) return;
    parent_->getStats()->useMana(manaCost_);
    coolDownTimer_ = 0.0f;
    //通过工厂模式创建Spell对象
    auto spell = spell_creator_->createSpell();
    spell->setPosition(pos);
    //播放攻击音效
    Game::getInstance().playSound(sound_path_);

}

bool Weapon::canAttack()
{
    if (coolDownTimer_ < coolDown_) return false;
    if (!parent_->getStats()->canUseMana(manaCost_)) return false;
    return true;
}
