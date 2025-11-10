#include "MoveControlArrow.h"

void MoveControlArrow::update(float deltaTime)
{
    MoveControl::update(deltaTime);
    auto keyboard = SDL_GetKeyboardState(NULL);
    is_up = keyboard[SDL_SCANCODE_UP];
    is_down = keyboard[SDL_SCANCODE_DOWN];
    is_left = keyboard[SDL_SCANCODE_LEFT];
    is_right = keyboard[SDL_SCANCODE_RIGHT];
}
