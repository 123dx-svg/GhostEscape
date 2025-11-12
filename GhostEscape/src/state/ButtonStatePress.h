#pragma once
#include "ButtonState.h"

class ButtonStatePress : public ButtonState
{
public:
    void onEnter() override;
    void onExit() override;
    bool handleEvent(SDL_Event& event) override;
};
