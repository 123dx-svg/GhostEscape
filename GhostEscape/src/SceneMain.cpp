#include "SceneMain.h"

#include <fstream>

#include "Enemy.h"
#include "Player.h"
#include "SceneTitle.h"
#include "Spawner.h"
#include "raw/BGStar.h"
#include "raw/Timer.h"
#include "screen/HUDButton.h"
#include "screen/HUDSkill.h"
#include "screen/HUDStats.h"
#include "screen/HUDText.h"
#include "screen/UIMouse.h"
#include "world/Effect.h"
#include "world/Spell.h"

void SceneMain::init()
{
    //隐藏鼠标
    SDL_HideCursor();
    //添加音乐
    Game::getInstance().playMusic("Asset/bgm/OhMyGhost.ogg");
    
    world_size_ = Game::getInstance().getScreenSize() * 3.f;
    camera_position_ = world_size_/2.f - Game::getInstance().getScreenSize()/2.f;//世界中心坐标
    //添加玩家
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_/2.f);
    addChild(player_);
    //星空背景
    BGStar::addBGStar(this,2000,0.2f,0.5f,0.3f);

    //默认三秒
    end_timer_ = Timer::addTimerChild(this);

    // 添加敌人生成器
    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    //按钮
    button_pause_ = HUDButton::addHUDButtonChild(this,Game::getInstance().getScreenSize()-glm::vec2(230,30),
        "Asset/UI/A_Pause1.png","Asset/UI/A_Pause2.png",
        "Asset/UI/A_Pause3.png"
        );
    button_restart_ = HUDButton::addHUDButtonChild(this,Game::getInstance().getScreenSize()-glm::vec2(140,30),
        "Asset/UI/A_Restart1.png","Asset/UI/A_Restart2.png",
        "Asset/UI/A_Restart3.png"
        );
    button_back_ = HUDButton::addHUDButtonChild(this,Game::getInstance().getScreenSize()-glm::vec2(50,30),
        "Asset/UI/A_Back1.png","Asset/UI/A_Back2.png",
        "Asset/UI/A_Back3.png"
        );




    //HUD
    hud_stats_ = HUDStats::addHUDStatsChild(this,player_,glm::vec2(30.f));
    //积分文本
    hud_text_score_ = HUDText::addHUDTextChild(this,"Score: 0",glm::vec2(Game::getInstance().getScreenSize().x -120.f,30.f),
        glm::vec2(200,50));

    //鼠标图标 
    ui_mouse_ = UIMouse::addUIMouse(this,"Asset/UI/29.png","Asset/UI/30.png",1);

    //创建武器图标
    auto scene = Game::getInstance().getCurrentScene();
    auto pos = glm::vec2(Game::getInstance().getScreenSize().x - 300,30);
    auto skill_hud = HUDSkill::addHUDSkillChild(scene, "Asset/UI/Electric-Icon.png", pos, 0.14f, Anchor::CENTER);
    player_->getWeapon()->setSkillHUD(skill_hud);
}

bool SceneMain::handleEvent(SDL_Event& event)
{
    if (Scene::handleEvent(event)) return true;
    return false;
}

void SceneMain::update(float deltaTime)
{
    checkSlowDown(deltaTime);
    Scene::update(deltaTime);
    updateScore();
    //检测按钮事件
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
    //检测定时器事件
    if (player_&&!player_->getActive())
    {
        end_timer_->start();
        saveData("Asset/score.dat");
    }
    checkEndTimer();

}

void SceneMain::render()
{
    //先渲染背景
    renderBackground();
    Scene::render();
    
}

void SceneMain::clean()
{
    Scene::clean();

}

void SceneMain::saveData(const std::string& file_path)
{
    Scene::saveData(file_path);
    auto score = Game::getInstance().getHighScore();
    std::ofstream file(file_path,std::ios::binary);//用二进制保存
    if (file.is_open())
    {
        file.write(reinterpret_cast<char*>(&score),sizeof(score));
        file.close();
    }
}

void SceneMain::renderBackground()
{
    //渲染窗口坐标 = 世界坐标 - 相机坐标
    auto start = - camera_position_;
    auto end = world_size_ - camera_position_;
    Game::getInstance().drawGrid(start,end,80,{0.5,0.5,0.5,1});
    Game::getInstance().drawBoundary(start,end,5,{1,1,1,1});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Score: " + std::to_string(Game::getInstance().getScore()));
}

void SceneMain::checkButtonPause()
{
    if (!button_pause_->getIsTrigger()) return;
    if (is_paused_) resume();
    else pause();

    
}

void SceneMain::checkButtonRestart()
{
    if (!button_restart_->getIsTrigger()) return;
    saveData("Asset/score.dat");
    Game::getInstance().setScore(0);
    auto scene = new SceneMain();
    Game::getInstance().safeChangeScene(scene);
}

void SceneMain::checkButtonBack()
{
    if (!button_back_->getIsTrigger()) return;
    saveData("Asset/score.dat");
    Game::getInstance().setScore(0);
    auto scene = new SceneTitle();
    Game::getInstance().safeChangeScene(scene);
}

void SceneMain::checkEndTimer()
{
    if (!end_timer_->timeOut()) return;
    pause();
    Game::getInstance().resumeMusic();
    //将原先按钮缩放并偏移
    button_restart_->setRenderPosition(Game::getInstance().getScreenSize()/2.f - glm::vec2(200.f,0.f));
    button_restart_->setScale(4.f);
    button_back_->setRenderPosition(Game::getInstance().getScreenSize()/2.f + glm::vec2(200.f,0.f));
    button_back_->setScale(4.f);
    button_pause_->setActive(false);
    //保证只执行一次checkEndTimer()
    end_timer_->stop();

}
void SceneMain::checkSlowDown(float& deltaTime)
{
    if (Game::getInstance().getMouseButtons()&SDL_BUTTON_RMASK)
    {
        deltaTime*=0.4f;
    }
}
