#include "core//Game.h"

//如果要测试请打开main
int  WinMain(int, char**) {

    auto& game = Game::getInstance();
    game.init("GhostEscape", 1280, 720);
    game.run();
    
    return 0;
}