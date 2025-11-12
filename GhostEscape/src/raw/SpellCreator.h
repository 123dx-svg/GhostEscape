#pragma once
#include "../core/Object.h"
#include "../world/Spell.h"

class SpellCreator : public Object
{
public:
    
    virtual Spell* createSpell()=0;
};
