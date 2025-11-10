#include "SceneTitle.h"

#include <fstream>

#include "SceneMain.h"
#include "screen/HUDButton.h"
#include "screen/HUDText.h"
#include "screen/UIMouse.h"


void SceneTitle::init()
{
    Scene::init();
    loadData("Asset/score.dat");
    SDL_HideCursor();
    Game::getInstance().playMusic("Asset/bgm/Spooky music.mp3");
    auto size = glm::vec2(Game::getInstance().getScreenSize().x/2.f,Game::getInstance().getScreenSize().y/3.f);
    //标题文本
    HUDText::addHUDTextChild(this,"Ghost Escape",
    Game::getInstance().getScreenSize()/2.f - glm::vec2(0,100),
    size,
    "Asset/font/VonwaonBitmap-16px.ttf",
    64
    );

    auto score_text = "Highest Score:" + std::to_string(Game::getInstance().getHighScore());
    //得分文本
    HUDText::addHUDTextChild(this,score_text,
    Game::getInstance().getScreenSize()/2.f + glm::vec2(0,100),
    glm::vec2(300,50),
    "Asset/font/VonwaonBitmap-16px.ttf",
    32
    );

    button_quit_ = HUDButton::addHUDButtonChild(this,
        Game::getInstance().getScreenSize()/2.f + glm::vec2(200,200),
    "Asset/UI/A_Quit1.png",
    "Asset/UI/A_Quit2.png",
    "Asset/UI/A_Quit3.png",
    2.f
    );
    button_start_ = HUDButton::addHUDButtonChild(this,
        Game::getInstance().getScreenSize()/2.f + glm::vec2(-200,200),
    "Asset/UI/A_Start1.png",
    "Asset/UI/A_Start2.png",
    "Asset/UI/A_Start3.png",
    2.f
    );
    button_credits_ = HUDButton::addHUDButtonChild(this,
        Game::getInstance().getScreenSize()/2.f + glm::vec2(0,200),
    "Asset/UI/A_Credits1.png",
    "Asset/UI/A_Credits2.png",
    "Asset/UI/A_Credits3.png",
    2.f
    );

    //文本
    auto text =  Game::getInstance().loadTextFile("Asset/credits.txt");
    credits_text_ = HUDText::addHUDTextChild(this,text,
    Game::getInstance().getScreenSize()/2.f ,
    glm::vec2(500,500),
    "Asset/font/VonwaonBitmap-16px.ttf",
    16
    );
    credits_text_->setBgSizeByText(50);
    credits_text_->setActive(false);

    //鼠标图标 
     ui_mouse_ = UIMouse::addUIMouse(this,"Asset/UI/pointer_c_shaded.png","Asset/UI/pointer_c_shaded.png",1,Anchor::TOP_LEFT);
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::update(float deltaTime)
{

    color_timer_ += deltaTime;
    updateColor();
    if (credits_text_->getActive())
    {
        //手动更新mouse
        ui_mouse_->update(deltaTime);
        return;
    }
    
    Scene::update(deltaTime);

    checkButtonQuit();
    checkButtonStart();
    checkButtonCredits();
}

bool SceneTitle::handleEvent(SDL_Event& event)
{
    //任意键推出credits_text_
    if (credits_text_->getActive())
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            credits_text_->setActive(false);
        }
        return true;
    }
    if (Scene::handleEvent(event)) return true;
    return false;
}

void SceneTitle::loadData(const std::string& file_path)
{
    int score = 0;
    Scene::loadData(file_path);
    std::ifstream file(file_path,std::ios::binary);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&score),sizeof(score));
        file.close();
    }
    Game::getInstance().setHighScore(score);
}

void SceneTitle::renderBackground()
{
    Game::getInstance().drawBoundary(glm::vec2(30.f),Game::getInstance().getScreenSize()-glm::vec2(30.f),10,boundary_color_);
}

void SceneTitle::updateColor()
{
    boundary_color_.r = 0.5f+ 0.5f*sinf(color_timer_*0.9f);
    boundary_color_.g = 0.5f+ 0.5f*sinf(color_timer_*0.8f);
    boundary_color_.b = 0.5f+ 0.5f*sinf(color_timer_*0.7f);
}

void SceneTitle::checkButtonQuit()
{
    if(button_quit_->getIsTrigger())
    {
        Game::getInstance().quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (button_start_->getIsTrigger())
    {
        auto scene = new SceneMain();
        Game::getInstance().safeChangeScene(scene);
    }
}

void SceneTitle::checkButtonCredits()
{
    if (button_credits_->getIsTrigger())
    {
        credits_text_->setActive(true);
    }
}
