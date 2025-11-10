#pragma once
#include "../affiliate/SpriteAnim.h"
#include "../core/ObjectWorld.h"

class Effect:public ObjectWorld
{
    SpriteAnim* sprite_ = nullptr;
    //播放完成后添加到场景中
    ObjectWorld* nextObject_ = nullptr;
public:

    static Effect* addEffectChild(Object* parent,const std::string& file_path,glm::vec2 pos,float scale = 1.f,ObjectWorld* nextObject = nullptr);
    
    virtual void update(float deltaTime) override;
    void clean() override;
    //get set
    SpriteAnim* getSprite() const {return sprite_;}
    void setSprite(SpriteAnim* sprite){sprite_ = sprite;}
    ObjectWorld* getNextObject() const {return nextObject_;}
    void setNextObject(ObjectWorld* nextObject){nextObject_ = nextObject;}


private:
    //检测动画是否播放完成
    void checkFinish();
};
