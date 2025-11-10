#include "HUDText.h"


HUDText* HUDText::addHUDTextChild(Object* parent, const std::string& text, const glm::vec2& render_pos,
    glm::vec2 size,const std::string& font_path, int font_size,const std::string& bg_path,  Anchor anchor)
{
    auto hud_text = new HUDText();
    hud_text->init();
    //设置渲染位置
    hud_text->setRenderPosition(render_pos);
    //先创建背景
    hud_text->setSpriteBg(Sprite::addSpriteChild(hud_text,bg_path,1,anchor));
    hud_text->setSize(size);
    hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text,text,font_path,font_size,anchor));
    if (parent)
    {
        parent->addChild(hud_text);
    }
    return hud_text;
}

void HUDText::setBgSizeByText(float margin)
{
    if (text_label_)
    {
        setSize(text_label_->getSize()+glm::vec2(margin));
    }
}

void HUDText::setSize(glm::vec2 size)
{
    size_ = size;
    sprite_bg_->setSize(size);
}

void HUDText::setBackground(const std::string& file_path)
{
    if (sprite_bg_)sprite_bg_->setTexture(file_path);
    else sprite_bg_ = Sprite::addSpriteChild(this,file_path);
    

}
