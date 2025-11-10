#pragma once
#include "../core/Object.h"

class MoveControl : public Object
{

protected:
    bool is_up = false;
    bool is_down = false;
    bool is_left = false;
    bool is_right = false;  
public:
    //getter
    bool getIsUp() const {return is_up;}
    bool getIsDown() const {return is_down;}
    bool getIsLeft() const {return is_left;}
    bool getIsRight() const {return is_right;}
};
