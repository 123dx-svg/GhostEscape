#pragma once
#include <random>
#include <string>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "AssetStore.h"

struct Texture;
class Scene;
class Game
{
    Game (){}
    Game(const Game&) =delete;
    Game& operator=(const Game&) =delete;

public:
    static Game& getInstance()//C++ 11之后最简单的单例模式 最推荐
    {
        static Game instance;
        return instance;
    }
private:
    AssetStore* asset_store_ = nullptr;//资源管理器
    glm::vec2 screen_size_ = glm::vec2(0);//屏幕大小
    glm::vec2 mouse_pos_ = glm::vec2(0);//鼠标位置
    SDL_MouseButtonFlags mouse_buttons_ = 0;//鼠标状态
    SDL_Window* window_ = nullptr;    //窗口
    SDL_Renderer* renderer_ = nullptr;//渲染器
    TTF_TextEngine* ttf_engine_ = nullptr;//字体引擎
    std::mt19937 gen_ = std::mt19937(std::random_device{}());//随机数生成器
    
    bool is_running_ = true;
    // Uint64 FPS_ = 60;//帧率
    // Uint64 frame_delay_ = 0;//帧延迟
    // float dt_ = 0.f;//帧间隔
    Scene* current_scene_ = nullptr;//当前场景
    Scene* next_scene_ = nullptr;//下一个场景

    int score_ = 0;//积分
    int high_score_ = 0;
    
public:


    //void run();//运行游戏
    void init(std::string title, int width, int height);//初始化游戏
    void handleEvents(SDL_Event& event);//处理事件
    void update(float deltaTime);//逻辑更新
    void render();//渲染游戏
    void clean();//清理游戏

    glm::vec2 getScreenSize() const{return screen_size_;}
    //获取当前场景
    Scene* getCurrentScene() const{return current_scene_;}
    //获取鼠标位置
    glm::vec2 getMousePos() const{return mouse_pos_;}
    //获取鼠标状态
    SDL_MouseButtonFlags getMouseButtons() const{return mouse_buttons_;}
    //获取积分
    int getScore() const{return score_;}
    //设置积分
    void setScore(int score);
    //获取最高积分
    int getHighScore() const{return high_score_;}
    //设置最高积分
    void setHighScore(int high_score){high_score_ = high_score;}
    //加分
    void addScore(int score);
    //退出游戏
    void quit(){is_running_ = false;}
    //是否退出游戏
    bool getIsRunning() const{return is_running_;}
    //安全切换场景
    //安全切换场景
    void safeChangeScene(Scene* new_scene){next_scene_ = new_scene;}
    //切换场景
    void changeScene(Scene* new_scene);

    //音频函数 方便以后换接口
    void playMusic(const std::string& music_path,bool loop = true){Mix_PlayMusic(asset_store_->getMusic(music_path),loop?-1:0);}//播放音乐 -1代表无线循环
    void playSound(const std::string& sound_path){Mix_PlayChannel(-1,asset_store_->getSound(sound_path),0);}//播放音效
    void stopMusic(){Mix_HaltMusic();}//停止音乐
    void stopSound(){Mix_HaltChannel(-1);}//停止音效
    void pauseMusic(){Mix_PauseMusic();}//暂停音乐
    void pauseSound(){Mix_Pause(-1);}//暂停音效
    void resumeMusic(){Mix_ResumeMusic();}//恢复音乐
    void resumeSound(){Mix_Resume(-1);}//恢复音效


    //渲染函数
    void renderTexture(const Texture& tex, const glm::vec2& pos, const glm::vec2& size,const glm::vec2& mask = glm::vec2(1.f));//以后渲染库变了也不用该其他地方
    void renderFillCircle(const glm::vec2& pos, const glm::vec2& size,float alpha);//debug圆形绘制
    void renderHBar(const glm::vec2& pos, const glm::vec2& size,float percent,SDL_FColor color);//渲染水平血条
    //绘制网格
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, int grid_width,SDL_FColor  color);
    //绘制边界
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, int boundary_width,SDL_FColor  color);
    // 文字渲染
    TTF_Text* createTTFText( const std::string& text,const std::string& font_path, int font_size = 16);
    //绘制点
    void drawPoint(const std::vector<glm::vec2>& points,glm::vec2 render_pos,SDL_FColor color);


    //工具函数
    bool isMouseInRect(const glm::vec2& top_left, const glm::vec2& button_right);//判断鼠标是否在矩形内
    std::string loadTextFile(const std::string& file_path);//加载文本文件

    //获取资源管理器
    AssetStore* getAssetStore() const{return asset_store_;}

    //随机数函数
    float randomFloat(float min, float max) {return std::uniform_real_distribution<float>(min, max)(gen_);}
    int randomInt(int min, int max) {return std::uniform_int_distribution<int>(min, max)(gen_);}
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max)
    {
        return {randomFloat(min.x, max.x), randomFloat(min.y, max.y)};
    }
    glm::ivec2 randomVec2i(const glm::ivec2& min, const glm::ivec2& max)
    {
        return {randomInt(min.x, max.x), randomInt(min.y, max.y)};
    }

private:
   //游戏鼠标位置 = （系统鼠标位置-偏移量）*缩放比例(逻辑分辨率/窗口大小)
    void updateMouse();
    //安全切换场景
    void checkChangeScene();
};


