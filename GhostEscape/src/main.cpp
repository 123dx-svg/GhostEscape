#define SDL_MAIN_USE_CALLBACKS 1
#include "core//Game.h"
#include <SDL3/SDL_main.h>


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  /* carry on with the program! */
    Game::getInstance().init("GhostEscape", 1280, 720);
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT|| !Game::getInstance().getIsRunning())
    {
        return SDL_APP_SUCCESS;
    }
    Game::getInstance().handleEvents(*event);
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

    static double deltaTime = 0;
    static Uint64 frame_delay = static_cast<Uint64>(1000000000.0 / 60.0);
    
    auto start_time = SDL_GetTicksNS();
    Game::getInstance().update(deltaTime);
    Game::getInstance().render();
    auto end_time = SDL_GetTicksNS();
    auto elapsed_time = end_time - start_time;
    //限制帧率为60
    if (elapsed_time < frame_delay)
    {
        SDL_DelayNS(frame_delay - elapsed_time);
        deltaTime = frame_delay/1000000000.0;
    }
    else
    {
        deltaTime = elapsed_time/1000000000.0;
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    Game::getInstance().clean();
}


//如果要测试请打开main
// int  WinMain(int, char**) {
//
//     auto& game = Game::getInstance();
//     game.init("GhostEscape", 1280, 720);
//     game.run();
//     
//     return 0;
// }