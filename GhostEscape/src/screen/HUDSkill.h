#pragma once
#include "../core/ObjectScreen.h"


class Sprite;

class HUDSkill : public ObjectScreen
{

protected:
    Sprite* icon_ = nullptr;
    float percentage_ = 1.f;
public:

    static HUDSkill* addHUDSkillChild(Object* parent , const std::string& file_path,glm::vec2 pos,float scale = 1.f,Anchor anchor= Anchor::CENTER);
    //让weapon的update更新percentage_


    //
    void render() override;

    //get set
    Sprite* getIcon() const {return icon_;}
    void setIcon(Sprite* icon) {icon_ = icon;}
    float getPercentage() const {return percentage_;}
    void setPercentage(float percentage);
    
    
};
