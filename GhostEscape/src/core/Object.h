#pragma once

#include "Game.h"
#include <vector>

#include "Defs.h"

class Object
{
protected:
    ObjectType type_ = ObjectType::NONE;
    //Game& game_ = Game::getInstance(); 没必要成员变量浪费空间
    std::vector<Object*> objectToAdd_;
    std::vector<Object*> children_;
    bool is_active_ = true;
    bool need_remove_ = false;//这样可以在下一轮循环时进行删除
public:
    Object(){}
    virtual ~Object()=default;//所有类，不在构造函数和析构函数做任何事情

    virtual void init(){} //需要初始化的事物，在这里实现
    virtual bool handleEvent(SDL_Event& event); //处理事件 如果事件被处理 返回true 否则返回false继续向下传递
    virtual void update(float deltaTime) ;
    virtual void render();
    virtual void clean() ;//需要清理的资源，在这里做

    //添加子对象
    virtual  void addChild(Object* child){children_.push_back(child);}
    //安全添加子对象
    void safeAddChild(Object* child){objectToAdd_.push_back(child);}
    //删除子对象
    virtual void removeChild(Object* child)
    {
        children_.erase(std::remove(children_.begin(),children_.end(),child),children_.end());
    }
    void setActive(bool active) {is_active_ = active;}
    bool getActive() const {return is_active_;}
    
    //获取对象类型
    ObjectType getType() const {return type_;}
    //设置对象类型
    void setType(ObjectType type) {type_ = type;}

    //是否需要删除
    bool getNeedRemove() const {return need_remove_;}
    //设置是否需要删除
    void setNeedRemove(bool need_remove) {need_remove_ = need_remove;}
};
