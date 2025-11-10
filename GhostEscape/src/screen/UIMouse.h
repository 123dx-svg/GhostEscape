#pragma once
#include "../core/ObjectScreen.h"
class Sprite;

class UIMouse:public ObjectScreen
{
protected:
    Sprite* sprite1_ = nullptr;
    Sprite* sprite2_ = nullptr;
    float timer_ = 0.0f;
    
public:
    void update(float deltaTime) override;

    static UIMouse* addUIMouse(Object* parent, const std::string& path1, const std::string& path2, float scale = 1.0f,Anchor anchor = Anchor::CENTER);
    //set get
    void setSprite1_(Sprite* sprite1_) {this->sprite1_ = sprite1_;}
    Sprite* getSprite1_() const {return sprite1_;}
    void setSprite2_(Sprite* sprite2_) {this->sprite2_ = sprite2_;}
    Sprite* getSprite2_() const {return sprite2_;}
};
