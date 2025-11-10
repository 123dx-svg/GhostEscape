#include "WeaponThunder.h"

#include "core/Actor.h"
#include "core/Scene.h"
#include "world/Spell.h"

void WeaponThunder::init()
{
    Weapon::init();
    //创建武器的时候就会同时创建图标
    auto scene = Game::getInstance().getCurrentScene();
    auto pos = glm::vec2(Game::getInstance().getScreenSize().x - 300,30);
    skill_hud_ = HUDSkill::addHUDSkillChild(scene, "Asset/UI/Electric-Icon.png", pos, 0.14f, Anchor::CENTER);
}

void WeaponThunder::update(float deltaTime)
{
    Weapon::update(deltaTime);
    if (skill_hud_) skill_hud_->setPercentage(coolDownTimer_/coolDown_);
}

WeaponThunder* WeaponThunder::addWeaponThunderChild(Actor* parent, float cool_down, float mana_cost)
{
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->coolDown_ = cool_down;
    weapon->manaCost_ = mana_cost;
    if (parent) parent->addChild(weapon);
    return weapon;
}

bool WeaponThunder::handleEvent(SDL_Event& event)
{
    Weapon::handleEvent(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
           if (canAttack())
           {
               Game::getInstance().playSound("Asset/sound/big-thunder.mp3");
               auto pos = Game::getInstance().getMousePos()+Game::getInstance().getCurrentScene()->getCameraPosition();
               auto spell = Spell::addSpellChild(nullptr, "Asset/effect/Thunderstrike w blur.png", pos, 40.f,3.f);
               attack(pos,spell);
               return true;
           }
        }
    }
    return false;
}
