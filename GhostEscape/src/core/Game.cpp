#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <fstream>

#include "../SceneTitle.h"
#include "../affiliate/Sprite.h"
// void Game::run()
// {
//     while (is_running_)
//     {
//         auto start = SDL_GetTicksNS();
//         //安全切换场景
//         if (next_scene_)
//         {
//             changeScene(next_scene_);
//             next_scene_ = nullptr;
//         }
//         handleEvents();
//         update(dt_);
//         render();
//         auto end = SDL_GetTicksNS();
//         auto elapsed = end - start;
//         //控制帧率
//         if (elapsed<frame_delay_){
//             SDL_DelayNS((frame_delay_ - elapsed));
//             dt_ = frame_delay_/1000000000.f;
//         }
//         else
//         {
//             dt_ = elapsed/1000000000.f;
//         }
//         //SDL_Log("FPS: %f",1.f/dt_);
//     }
// }

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    //SDL3初始化
    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_Mixer初始化失败: %s\n",SDL_GetError());
    }
    if (!Mix_OpenAudio(0,NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_Mixer初始化失败: %s\n",SDL_GetError());
    }
    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
    Mix_Volume(-1,MIX_MAX_VOLUME/4);
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_TTF初始化失败: %s\n",SDL_GetError());
    }
    //同时创建窗口和渲染器
    SDL_CreateWindowAndRenderer(title.c_str(),width,height,SDL_WINDOW_RESIZABLE,&window_,&renderer_);
    if (!window_||!renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"创建窗口和渲染器失败: %s\n",SDL_GetError());
    }
    //设置窗口逻辑分辨率 宽高比不变
    SDL_SetRenderLogicalPresentation(renderer_,width,height,SDL_LOGICAL_PRESENTATION_LETTERBOX);

    //创建字体引擎
    ttf_engine_ = TTF_CreateRendererTextEngine(renderer_);
    
    //单位为纳秒
    // frame_delay_ = 1000000000/FPS_;

    //创建资源管理器
    asset_store_ = new AssetStore(renderer_);

    //创建场景
    current_scene_ = new SceneTitle();
    current_scene_->init();
}

void Game::handleEvents(SDL_Event& event)
{
    // while (SDL_PollEvent(&event)){
    //     switch (event.type){
    //         case SDL_EVENT_QUIT:
    //             is_running_ = false;
    //             break;
    //         default:
               current_scene_->handleEvent(event);
    //     }
    // }
}

void Game::update(float deltaTime)
{
    //安全切换场景
    checkChangeScene();
    updateMouse();
    current_scene_->update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_,0,0,0,255);
    SDL_RenderClear(renderer_);
    current_scene_->render();
    SDL_RenderPresent(renderer_);
}

void Game::clean()
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
    }
    if (asset_store_)
    {
        asset_store_->clear();
        delete asset_store_;
    }

    //释放字体引擎
    if (ttf_engine_)
        TTF_DestroyRendererTextEngine(ttf_engine_);
    
    //释放资源
    if (renderer_)
        SDL_DestroyRenderer(renderer_);
    if (window_)
        SDL_DestroyWindow(window_);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void Game::setScore(int score)
{
    score_ = score;
    //更新最高积分
    high_score_ = std::max(score_, high_score_);
}


void Game::addScore(int score)
{
    setScore(score_ + score);
}

void Game::changeScene(Scene* new_scene)
{
    if (current_scene_)
    {
        current_scene_->clean();
        delete current_scene_;
    }
    current_scene_ = new_scene;
    current_scene_->init();
}

void Game::renderTexture(const Texture& tex, const glm::vec2& pos, const glm::vec2& size,const glm::vec2& mask)
{

    //如果只想渲染图片一半区域，需要调整src_rect和dst_rect
    SDL_FRect src_rect = {
        tex.src_rect.x,
        tex.src_rect.y+tex.src_rect.h*(1-mask.y),//从下往上渲染
        tex.src_rect.w * mask.x,
        tex.src_rect.h * mask.y
    };
    
    SDL_FRect dst_rect = {
        pos.x,
        pos.y + size.y*(1-mask.y),//从下往上渲染
        size.x*mask.x,
        size.y*mask.y
    };
    SDL_RenderTextureRotated(renderer_,tex.texture,&src_rect, &dst_rect, tex.angle,nullptr, tex.is_flip?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

void Game::renderFillCircle(const glm::vec2& pos, const glm::vec2& size, float alpha)
{
    auto texture = asset_store_->getImage("Asset/UI/circle.png");
    SDL_FRect dst_rect = {
        pos.x,
        pos.y,
        size.x,
        size.y
    };
    SDL_SetTextureAlphaModFloat(texture,alpha);
    SDL_RenderTexture(renderer_,texture, nullptr,&dst_rect);
}

void Game::renderHBar(const glm::vec2& pos, const glm::vec2& size, float percent, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    SDL_FRect boundary_rect = {
        pos.x,
        pos.y,
        size.x,
        size.y
    };
    SDL_FRect fill_rect = {
        pos.x,
        pos.y,
        size.x*percent,
        size.y
    };
    SDL_RenderRect(renderer_, &boundary_rect);
    SDL_RenderFillRect(renderer_, &fill_rect);
    SDL_SetRenderDrawColorFloat(renderer_,0,0,0,1);
}

TTF_Text* Game::createTTFText(const std::string& text, const std::string& font_path, int font_size)
{
    auto font = asset_store_->getFont(font_path,font_size);
    return TTF_CreateText(ttf_engine_,font,text.c_str(),0);
}

void Game::drawPoint(const std::vector<glm::vec2>& points, glm::vec2 render_pos, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_,color.r,color.g,color.b,color.a);
    for (const auto& point : points)
    {
        SDL_RenderPoint(renderer_, point.x+render_pos.x, point.y+render_pos.y);
    }
    SDL_SetRenderDrawColorFloat(renderer_,0,0,0,1);
}

bool Game::isMouseInRect(const glm::vec2& top_left, const glm::vec2& button_right)
{
    return mouse_pos_.x >= top_left.x && mouse_pos_.x <= button_right.x &&
           mouse_pos_.y >= top_left.y && mouse_pos_.y <= button_right.y;
}

std::string Game::loadTextFile(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"打开文件失败: %s\n",file_path.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

bool Game::isRectCollideRect(const glm::vec2& top_left1, const glm::vec2& bottom_right1, const glm::vec2& top_left2,
    const glm::vec2& bottom_right2)
{
    //aabb碰撞检测
    return top_left1.x < bottom_right2.x && bottom_right1.x > top_left2.x &&
           top_left1.y < bottom_right2.y && bottom_right1.y > top_left2.y;
}

bool Game::isRectInRect(const glm::vec2& top_left1, const glm::vec2& bottom_right1, const glm::vec2& top_left2,
    const glm::vec2& bottom_right2)
{
    //判断矩形1是否完全在矩形2内
    return top_left1.x > top_left2.x && bottom_right1.x < bottom_right2.x &&
           top_left1.y > top_left2.y && bottom_right1.y < bottom_right2.y;
}

void Game::updateMouse()
{
    //处理屏幕缩放导致的鼠标偏移
    mouse_buttons_ = SDL_GetMouseState(&mouse_pos_.x, &mouse_pos_.y);
    int w,h;
    SDL_GetWindowSize(window_,&w,&h);
    //锁死窗口缩放比例
    SDL_SetWindowAspectRatio(window_,screen_size_.x/screen_size_.y,screen_size_.x/screen_size_.y);
    mouse_pos_*=screen_size_/glm::vec2(w,h);
    
    //保持黑边，不限制比例做法

    
    // SDL_FRect rect;
    // SDL_GetRenderLogicalPresentationRect(renderer_, &rect);
    // mouse_pos_ = (mouse_pos_ - glm::vec2(rect.x,rect.y)) * screen_size_/glm::vec2(rect.w,rect.h);
}

void Game::checkChangeScene()
{
    if (next_scene_)
    {
        changeScene(next_scene_);
        next_scene_ = nullptr;
    }
}

void Game::drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, int grid_width, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r , color.g, color.b, color.a);
    //绘制竖线 mod为取余运算 起点之前终点之后的线就不计算绘制了
    for (float x = glm::mod(top_left.x,static_cast<float>(grid_width)); x <= screen_size_.x; x += grid_width)
    {
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    //绘制横线
    for (float y = glm::mod(top_left.y,static_cast<float>(grid_width)); y <= screen_size_.y; y += grid_width)
    {
        SDL_RenderLine(renderer_,top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, int boundary_width, SDL_FColor color)
{
    if (!isRectCollideRect(top_left - glm::vec2(boundary_width),bottom_right + glm::vec2(boundary_width),glm::vec2(0),screen_size_)
        ||isRectInRect(glm::vec2(0),screen_size_,top_left,bottom_right))
    {
        return;
    }
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    for (float i = 0; i < boundary_width; ++i)
    {
        SDL_FRect rect ={
            top_left.x-i,
            top_left.y-i,
            bottom_right.x-top_left.x+i*2,
            bottom_right.y-top_left.y+i*2
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}
