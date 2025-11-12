#pragma once
#include "SpellCreator.h"

class FireSpellCreator:public SpellCreator
{
public:
    Spell* createSpell() override;
};
