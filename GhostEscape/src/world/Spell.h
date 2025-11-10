#pragma once
#include "../affiliate/SpriteAnim.h"
#include "../core/ObjectWorld.h"

class Spell : public ObjectWorld
{

protected:
    SpriteAnim* sprite_ = nullptr;
    float damage_ = 60.0f;
public:
    static Spell* addSpellChild(Object* parent,const std::string& file_path,glm::vec2 pos,float damage,float scale = 1.f,Anchor anchor = Anchor::CENTER);
    
    void update(float deltaTime) override;
    void setSprite(SpriteAnim* spr) {sprite_ = spr;}
    float getDamage() const {return damage_;}
    void setDamage(float damage) {damage_ = damage;}
    SpriteAnim* getSprite() const {return sprite_;}
    void setSpriteAnim(SpriteAnim* spr) {sprite_ = spr;}
private:
    void attack();
    
};
