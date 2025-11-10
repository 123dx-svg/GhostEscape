#include "Sprite.h"

Texture::Texture(const std::string& file_path)
{
    texture = Game::getInstance().getAssetStore()->getImage(file_path);
    SDL_GetTextureSize(texture,&src_rect.w,&src_rect.h);
}

void Sprite::render()
{
    ObjectAffiliate::render();
    if (texture_.texture ==  nullptr || !parent_ || is_finish_)
        return;
    auto pos = parent_->getRenderPosition()+offset_;
    Game::getInstance().renderTexture(texture_,pos,size_,percentage_);//解耦方法
}

Sprite* Sprite::addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale,Anchor anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setAnchor(anchor);
    sprite->setTexture(Texture(file_path));
    sprite->setScale(scale);
    sprite->setParent(parent);
    parent->addChild(sprite);
    return sprite;
}

void Sprite::setTexture(const Texture& texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w,texture.src_rect.h);
}
