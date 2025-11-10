#include "MoveControlWASD.h"

void MoveControlWASD::update(float deltaTime)
{
    MoveControl::update(deltaTime);
    auto keyboard = SDL_GetKeyboardState(NULL);
    is_up = keyboard[SDL_SCANCODE_W];
    is_down = keyboard[SDL_SCANCODE_S];
    is_left = keyboard[SDL_SCANCODE_A];
    is_right = keyboard[SDL_SCANCODE_D];
}
