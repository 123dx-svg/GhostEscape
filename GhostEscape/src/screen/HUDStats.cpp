#include "HUDStats.h"

#include "../core/Actor.h"
#include "../raw/Stats.h"

HUDStats* HUDStats::addHUDStatsChild(Object* parent, Actor* target, glm::vec2 render_pos)
{
    auto hud_stats = new HUDStats();
    hud_stats->init();
    hud_stats->setRenderPosition(render_pos);
    hud_stats->setTarget(target);
    if (parent)parent->addChild(hud_stats);
    
    return hud_stats;
}

void HUDStats::init()
{
    ObjectScreen::init();
    //添加子元素 创建顺序需要和渲染顺序一致 
    health_bar_bg_ = Sprite::addSpriteChild(this,"Asset/UI/bar_bg.png",3.f,Anchor::CENTER_LEFT);
    health_bar_bg_->setOffset(health_bar_bg_->getOffset()+ glm::vec2(30,0));
    health_bar_ = Sprite::addSpriteChild(this,"Asset/UI/bar_red.png",3.f,Anchor::CENTER_LEFT);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(30,0));
    health_icon_ = Sprite::addSpriteChild(this,"Asset/UI/Red Potion.png",0.5f,Anchor::CENTER_LEFT);

    mana_bar_bg_ = Sprite::addSpriteChild(this,"Asset/UI/bar_bg.png",3.f,Anchor::CENTER_LEFT);
    mana_bar_bg_->setOffset(mana_bar_bg_->getOffset()+ glm::vec2(300,0));
    mana_bar_ = Sprite::addSpriteChild(this,"Asset/UI/bar_blue.png",3.f,Anchor::CENTER_LEFT);
    mana_bar_->setOffset(mana_bar_->getOffset() + glm::vec2(300,0));
    mana_icon_ = Sprite::addSpriteChild(this,"Asset/UI/Blue Potion.png",0.5f,Anchor::CENTER_LEFT);
    mana_icon_->setOffset(mana_icon_->getOffset() + glm::vec2(270,0));
}

void HUDStats::update(float deltaTime)
{
    ObjectScreen::update(deltaTime);
    //获取Actor的生命百分比
    updateHealthBar();
    updateManaBar();
}

void HUDStats::updateHealthBar()
{
    if (!target_||!health_bar_||!target_->getStats()) return;
    health_bar_->setPercentage(glm::vec2(target_->getStats()->getHealth()/target_->getStats()->getMaxHealth(),1.f));
   
}

void HUDStats::updateManaBar()
{
    if (!target_||!mana_bar_||!target_->getStats()) return;
    mana_bar_->setPercentage(glm::vec2(target_->getStats()->getMana()/target_->getStats()->getMaxMana(),1.f));
}
