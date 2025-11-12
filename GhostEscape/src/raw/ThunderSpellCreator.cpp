#include "ThunderSpellCreator.h"
#include "../core/Scene.h"

Spell* ThunderSpellCreator::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(),"Asset/effect/Thunderstrike w blur.png",
        glm::vec2(0),40.f,3.f);
}
