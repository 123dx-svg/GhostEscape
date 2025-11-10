#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include "ObjectWorld.h"

class Scene : public Object
{
protected:
    //世界大小
    glm::vec2 world_size_ = glm::vec2(0);
    glm::vec2 camera_position_ = glm::vec2(0);
    std::vector<ObjectWorld*> children_world_;
    std::vector<ObjectScreen*> children_screen_;
    //暂停游戏标记
    bool is_paused_ = false;

public:
    Scene() = default;
    ~Scene() override=default;//所有类，不在构造函数和析构函数做任何事情

    virtual void init() override{} //需要初始化的事物，在这里实现
    bool handleEvent(SDL_Event& event) override ;
    void update(float deltaTime) override ;
    void render() override ;
    void clean() override ;
    virtual void addChild(Object* child) override;
    virtual void removeChild(Object* child) override;

    //二进制存档接口
    virtual void saveData(const std::string& file_path) {}
    //加载存档接口
    virtual void loadData(const std::string& file_path) {}
    

    //世界坐标转屏幕
    glm::vec2 worldToScreen(const glm::vec2& world_pos) const {return world_pos - camera_position_;}
    //屏幕坐标转世界
    glm::vec2 screenToWorld(const glm::vec2& screen_pos) const {return screen_pos + camera_position_;}

    void pause() {Game::getInstance().pauseMusic();Game::getInstance().pauseSound();is_paused_ = true;}
    void resume() {Game::getInstance().resumeMusic();Game::getInstance().resumeSound();is_paused_ = false;}

    glm::vec2 getCameraPosition() const {return camera_position_;}
    void setCameraPosition(const glm::vec2& pos) ;

    glm::vec2 getWorldSize() const {return world_size_;}
    void setWorldSize(const glm::vec2& size) {world_size_ = size;}

    std::vector<ObjectScreen*>& getChildrenScreen()  {return children_screen_;}
    std::vector<ObjectWorld*>& getChildrenWorld()  {return children_world_;}
    
};
