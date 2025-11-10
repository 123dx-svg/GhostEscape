#pragma once
#include "../affiliate/Sprite.h"
#include "../affiliate/TextLabel.h"
#include "../core/ObjectScreen.h"

class HUDText:public ObjectScreen
{
protected:
    TextLabel* text_label_ = nullptr;
    Sprite* sprite_bg_ = nullptr;
    glm::vec2 size_ = glm::vec2(0,0);//背景大小
public:

    static HUDText* addHUDTextChild(Object* parent,const std::string& text,const glm::vec2& render_pos,
        glm::vec2 size,const std::string& font_path = "Asset/font/VonwaonBitmap-16px.ttf",
        int font_size= 32,const std::string& bg_path = "Asset/UI/Textfield_01.png",
        Anchor anchor = Anchor::CENTER);

    //根据文本动态调整大小
    void setBgSizeByText(float margin = 10.f);
    
    //set get
    void setTextLabel(TextLabel* text_label) {text_label_ = text_label;}
    TextLabel* getTextLabel() {return text_label_;}
    void setSpriteBg(Sprite* sprite_bg) {sprite_bg_ = sprite_bg;}
    Sprite* getSpriteBg() {return sprite_bg_;}
    glm::vec2 getSize() {return size_;}
    void setSize(glm::vec2 size);


    //设置和获取文本
    void setText(const std::string& text){text_label_->setText(text);}
    std::string getText(){return text_label_->getText();}

    void setBackground(const std::string& file_path);
};
