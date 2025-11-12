#include "FireSpellCreator.h"
#include "../core/Scene.h"

Spell* FireSpellCreator::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(),"Asset/effect/Explosion 2 SpriteSheet.png",
        glm::vec2(0),20.f,3.f);
}
