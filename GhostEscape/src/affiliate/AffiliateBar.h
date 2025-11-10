#pragma once
#include "../core/ObjectAffiliate.h"

/*血条组件*/
class AffiliateBar : public ObjectAffiliate
{
protected:
    float percentage_ = 1.f;
    SDL_FColor color_high_ = {0,1,0,1};
    SDL_FColor color_mid_ = {1.f,0.65f,0.f,1.f};
    SDL_FColor color_low_ = {1,0,0,1};
    
public:

    static AffiliateBar* addAffiliateBarChild(ObjectScreen* parent,glm::vec2 size = glm::vec2(0,0),Anchor anchor = Anchor::CENTER);
    void render() override;

    
    //get set
    float getPercentage() { return percentage_; }
    void setPercentage(float percentage) { percentage_ = percentage; }
    SDL_FColor getColorHigh() { return color_high_; }
    void setColorHigh(SDL_FColor color_high) { color_high_ = color_high; }
    SDL_FColor getColorMid() { return color_mid_; }
    void setColorMid(SDL_FColor color_mid) { color_mid_ = color_mid; }
    SDL_FColor getColorLow() { return color_low_; }
    void setColorLow(SDL_FColor color_low) { color_low_ = color_low; }
    
    
};
