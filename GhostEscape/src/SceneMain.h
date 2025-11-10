#pragma once
#include "core/Scene.h"

class Timer;
class HUDButton;
class HUDText;
class HUDStats;
class UIMouse;
class Spawner;
class Player;

class SceneMain : public Scene
{


    //玩家
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    //鼠标
    UIMouse* ui_mouse_ = nullptr;
    HUDStats* hud_stats_ = nullptr;
    //积分文本
    HUDText* hud_text_score_ = nullptr;
    //按钮
    HUDButton* button_pause_ = nullptr;
    HUDButton* button_restart_ = nullptr;
    HUDButton* button_back_ = nullptr;
    //定时器
    Timer* end_timer_ = nullptr;
    
public:
    SceneMain(){}
    ~SceneMain() override=default;//所有类，不在构造函数和析构函数做任何事情

    void init() override; //需要初始化的事物，在这里实现
    bool handleEvent(SDL_Event& event) override;
    void update(float deltaTime) override ;
    void render() override ;
    void clean() override ;//需要清理的资源，在这里做

    void saveData(const std::string& file_path) override;

private:
    void renderBackground();
    void updateScore();
    //按钮事件
    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();
    void checkEndTimer();
    void checkSlowDown(float& deltaTime);
    
};


