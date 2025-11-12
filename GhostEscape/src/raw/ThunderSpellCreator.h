#pragma once
#include "SpellCreator.h"

class ThunderSpellCreator:public SpellCreator
{
public:
    Spell* createSpell() override;
};
