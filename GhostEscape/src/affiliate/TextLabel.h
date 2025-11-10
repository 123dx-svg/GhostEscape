#pragma once
#include "../core/ObjectAffiliate.h"

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text* ttf_text_ = nullptr;
    std::string font_path_ = "";
    int font_size_ = 16;
public:

    static TextLabel* addTextLabelChild(ObjectScreen* parent,const std::string& text ,const std::string& font_path,int font_size,Anchor anchor = Anchor::CENTER);
    
    void render() override;
    void clean() override;
    //set get
    void setFont(const std::string& font_path,int font_size);//init之后需要立即调用
    void setFontPath(const std::string& font_path);
    void setFontSize(int font_size);
    void setText(std::string text);
    std::string getText() const {return ttf_text_->text;}

private:
    void updateSize();
    
};
