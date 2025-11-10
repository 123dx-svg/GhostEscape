#pragma once
#include "../core/ObjectAffiliate.h"

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = {0,0,0,0};
    float angle = 0;
    bool is_flip = false;
    Texture() = default;
    Texture(const std::string& file_path);
};

/**
 * 精灵
 */
class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;
    bool is_finish_ = false;
    glm::vec2 percentage_ = glm::vec2(1.f);//决定图片原始区域的百分比 横纵都有百分比

public:

    void render() override;

    static Sprite* addSpriteChild(ObjectScreen* parent,const std::string& file_path,float scale = 1.f,Anchor anchor = Anchor::CENTER);
    
   //get set
    Texture getTexture() const {return texture_;}
    virtual  void setTexture(const Texture& texture);
    void setFlip(bool is_flip) {texture_.is_flip = is_flip;}
    void setAngle(float angle) {texture_.angle = angle;}
    bool getFlip() const {return texture_.is_flip;}
    float getAngle() const {return texture_.angle;}

    bool getFinish() const {return is_finish_;}
    void setFinish(bool is_finish){is_finish_ = is_finish;}
    
    void setPercentage(const glm::vec2& percentage) {percentage_ = percentage;}
    glm::vec2 getPercentage() const {return percentage_;}
    
    
};
