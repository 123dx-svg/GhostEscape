#include "HUDSkill.h"

#include "../affiliate/Sprite.h"

HUDSkill* HUDSkill::addHUDSkillChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale,
                                     Anchor anchor)
{
    
    auto skill = new HUDSkill();
    skill->init();
    skill->icon_ = Sprite::addSpriteChild(skill, file_path, scale, anchor);
    skill->setRenderPosition(pos);
    if (parent) parent->addChild(skill);
    return skill;
}

void HUDSkill::render()
{
    //灰色图标背景
    SDL_SetTextureColorModFloat(icon_->getTexture().texture,0.3f,0.3f,0.3f);
    auto pos = getRenderPosition() + icon_->getOffset();
    Game::getInstance().renderTexture(icon_->getTexture(),pos,icon_->getSize());
    SDL_SetTextureColorModFloat(icon_->getTexture().texture,1.f,1.f,1.f);
    ObjectScreen::render();
    
}

void HUDSkill::setPercentage(float percentage)
{
    percentage = glm::clamp(percentage, 0.0f, 1.0f);
    percentage_ = percentage;
    if (icon_)
        icon_->setPercentage(glm::vec2(1.f,percentage_));
}

