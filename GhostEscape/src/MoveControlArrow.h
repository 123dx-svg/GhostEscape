#pragma once
#include "raw/MoveControl.h"

class MoveControlArrow:public MoveControl
{
public:
    void update(float deltaTime) override;
};
