#pragma once
#include "core/Scene.h"

class UIMouse;
class HUDText;
class HUDButton;

class SceneTitle: public Scene
{

protected:
    SDL_FColor boundary_color_ = {0.5,0.5,0.5,1};
    float color_timer_ = 0.0f;

    //三个按钮
    HUDButton* button_start_ = nullptr;
    HUDButton* button_quit_ = nullptr;
    HUDButton* button_credits_ = nullptr;
    HUDText* credits_text_ = nullptr;
    UIMouse* ui_mouse_ = nullptr;

    
public:
    void init() override;
    void render() override;
    void update(float deltaTime) override;
    bool handleEvent(SDL_Event& event) override;

    void loadData(const std::string& file_path) override;
private:
    
    
    void renderBackground();
    //RGB颜色
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
};
