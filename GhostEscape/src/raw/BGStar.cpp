#include "BGStar.h"

#include "../core/Scene.h"

BGStar* BGStar::addBGStar(Object* parent, int num, float scale_far, float scale_mid, float scale_near)
{
    auto star = new BGStar();
    star->init();
    star->num_ = num;
    star->scale_far_ = scale_far;
    star->scale_mid_ = scale_mid;
    star->scale_near_ = scale_near;
    //预分配内存
    star->star_far_.reserve(num);
    star->star_mid_.reserve(num);
    star->star_near_.reserve(num);
    //场景大小比屏幕大小多出来的部分
    auto extra = Game::getInstance().getCurrentScene()->getWorldSize() - Game::getInstance().getScreenSize();
    for (int i = 0; i < num; ++i)
    {
        star->star_far_.push_back(Game::getInstance().randomVec2(glm::vec2(0),Game::getInstance().getScreenSize()+extra*scale_far));
        star->star_mid_.push_back(Game::getInstance().randomVec2(glm::vec2(0),Game::getInstance().getScreenSize()+extra*scale_mid));
        star->star_near_.push_back(Game::getInstance().randomVec2(glm::vec2(0),Game::getInstance().getScreenSize()+extra*scale_near));
    }
    if (parent)
        parent->addChild(star);

    return star;
}

void BGStar::update(float deltaTime)
{
    Object::update(deltaTime);
    //更新颜色
    timer_ += deltaTime;
    color_far_ = {0.5f+0.5f*sinf(timer_*0.9f),0.5f+0.5f*sinf(timer_*0.8f),0.5f+0.5f*sinf(timer_*0.7f),1};
    color_mid_ = {0.5f+0.5f*sinf(timer_*0.8f),0.5f+0.5f*sinf(timer_*0.7f),0.5f+0.5f*sinf(timer_*0.6f),1};
    color_near_ = {0.5f+0.5f*sinf(timer_*0.7f),0.5f+0.5f*sinf(timer_*0.6f),0.5f+0.5f*sinf(timer_*0.5f),1};
}

void BGStar::render()
{
    Object::render();
    Game::getInstance().drawPoint(star_far_,-Game::getInstance().getCurrentScene()->getCameraPosition()*scale_far_,color_far_);
    Game::getInstance().drawPoint(star_mid_,-Game::getInstance().getCurrentScene()->getCameraPosition()*scale_mid_,color_mid_);
    Game::getInstance().drawPoint(star_near_,-Game::getInstance().getCurrentScene()->getCameraPosition()*scale_near_,color_near_);
}
