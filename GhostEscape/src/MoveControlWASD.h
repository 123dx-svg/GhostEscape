#pragma once
#include "raw/MoveControl.h"

class MoveControlWASD:public MoveControl
{
public:
    void update(float deltaTime) override;
};
