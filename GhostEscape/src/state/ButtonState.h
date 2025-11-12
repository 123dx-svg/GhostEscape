#pragma once
#include "../core/Object.h"
#include "../screen/HUDButton.h"

class ButtonState:public Object
{
    
protected:
    HUDButton* parent_ = nullptr;
public:
    virtual void onEnter()=0;
    virtual void onExit()=0;
    
    //set get
    HUDButton* getParent(){return parent_;}
    void setParent(HUDButton* parent){parent_ = parent;}
    
    
};
