#pragma once
#include "../core/Object.h"

/**
 * @brief 背景星星
 * 
 */
class BGStar : public Object
{

protected:
    std::vector<glm::vec2> star_far_;
    std::vector<glm::vec2> star_mid_;
    std::vector<glm::vec2> star_near_;
    //越近距，移动越快
    float scale_far_ = 0.2f;
    float scale_mid_ = 0.5f;
    float scale_near_ = 0.7f;
    //星星颜色
    SDL_FColor color_far_ = {0,0,0,1};
    SDL_FColor color_mid_ = {0,0,0,1};
    SDL_FColor color_near_ = {0,0,0,1};
    float timer_ = 0;
    int num_ = 2000;//每层的星星数量
public:
    static BGStar* addBGStar(Object* parent,int num,float scale_far,float scale_mid,float scale_near);
    void update(float deltaTime) override;
    void render() override;
};
