#pragma once
#include "ObjectScreen.h"
#include "../affiliate/Collider.h"

class ObjectWorld:public ObjectScreen
{
protected:
    glm::vec2 position_  = glm::vec2(0.0f);//世界位置
    Collider* collider_ = nullptr;//碰撞组件

public:
    void init() override;
    void update(float deltaTime) override;

    virtual  void takeDamage(float damage) {return;}
    
    virtual ObjectWorld* clone() {return nullptr;} //用到的子类重写
    
    virtual  glm::vec2 getPosition() const override {return position_;}
    void setPosition(const glm::vec2& position);
    virtual void setRenderPosition(const glm::vec2& pos) override;

    Collider* getCollider() const {return collider_;}
    void setCollider(Collider* collider){collider_ = collider;}
};
