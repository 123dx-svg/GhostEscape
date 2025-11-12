#pragma once
#include "ButtonState.h"

class ButtonStateHover : public ButtonState
{
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    bool handleEvent(SDL_Event& event) override;
    
};
