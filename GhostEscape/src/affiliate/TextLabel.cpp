#include "TextLabel.h"

TextLabel* TextLabel::addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& font_path,
    int font_size,Anchor anchor)
{
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setFont(font_path,font_size);
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->updateSize();
    if (parent)
    {
        parent->addChild(text_label);
        text_label->setParent(parent);
    }
    return text_label;
}


void TextLabel::render()
{
    ObjectAffiliate::render();
    const auto pos = parent_->getRenderPosition()+offset_;//这个只有ObjectScreen才会有
    TTF_DrawRendererText(ttf_text_,pos.x,pos.y);
}

void TextLabel::clean()
{
    ObjectAffiliate::clean();
    if (ttf_text_)
        TTF_DestroyText(ttf_text_);
}

void TextLabel::setFont(const std::string& font_path, int font_size)
{
    font_size_ = font_size;
    font_path_ = font_path;
    auto font = Game::getInstance().getAssetStore()->getFont(font_path_,font_size_);
    if (!ttf_text_) ttf_text_ = Game::getInstance().createTTFText("",font_path_,font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontPath(const std::string& font_path)
{
    font_path_ = font_path;
    //有可能是新的font 所以从AssetStore里载入
    //然后设置TTF_text里的ttf_font
    auto font = Game::getInstance().getAssetStore()->getFont(font_path_,font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
    
}

void TextLabel::setFontSize(int font_size)
{
    font_size_ = font_size;
    //有可能是新的font_size 所以从AssetStore里载入
    //然后设置TTF_text里的ttf_font
    auto font = Game::getInstance().getAssetStore()->getFont(font_path_,font_size);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setText(std::string text)
{
    TTF_SetTextString(ttf_text_,text.c_str(),text.length());
    updateSize();
}

void TextLabel::updateSize()
{
    int w,h;
    TTF_GetTextSize(ttf_text_,&w,&h);
    //不仅设置大小还有对其方式
    setSize(glm::vec2(w,h));
}
