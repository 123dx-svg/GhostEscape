#include "SpriteAnim.h"

SpriteAnim* SpriteAnim::addSpriteAnimChild(ObjectScreen* parent,const std::string& file_path, float scale,Anchor anchor )
{
    auto spriteAnim = new SpriteAnim();
    spriteAnim->init();
    spriteAnim->setAnchor(anchor);
    spriteAnim->setTexture(Texture(file_path));
    spriteAnim->setScale(scale);
    spriteAnim->setParent(parent);
    parent->addChild(spriteAnim);
    return spriteAnim;
}

void SpriteAnim::update(float deltaTime)
{
    Sprite::update(deltaTime);
    
    if (is_finish_) return;
    
    frame_timer_ += deltaTime;
    if(frame_timer_ >= 1.f/fps_)
    {
        current_frame_++;
        if(current_frame_ >= total_frames_)
        {
            current_frame_ = 0;
            if (!is_loop_) is_finish_ = true;
        }
        frame_timer_ = 0.f;
    }
    texture_.src_rect.x = texture_.src_rect.w * current_frame_;
}

void SpriteAnim::setTexture(const Texture& texture)
{
    texture_ = texture;
    total_frames_ = static_cast<int>(texture.src_rect.w / texture.src_rect.h);
    texture_.src_rect.w = texture.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w,texture_.src_rect.h);
}
