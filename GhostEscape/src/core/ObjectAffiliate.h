#pragma once
#include "ObjectScreen.h"

/**
 * 偏移 尺寸 父节点
 */
class ObjectAffiliate:public Object
{
protected:
    ObjectScreen* parent_ = nullptr;//父节点怎么样子都得有坐标
    glm::vec2 offset_ = glm::vec2(0);//偏移
    glm::vec2 size_ = glm::vec2(0);//尺寸
    //Anchor锚点
    Anchor anchor_ = Anchor::CENTER;

public:
    void setOffsetByAnchor(Anchor anchor);
    
    //设置和获取函数
    void setOffset(const glm::vec2& offset) {offset_ = offset;}
    glm::vec2 getOffset() const {return offset_;}
    void setSize(const glm::vec2& size);
    glm::vec2 getSize() const {return size_;}
    void setParent(ObjectScreen* parent) {parent_ = parent;}
    ObjectScreen* getParent() const {return parent_;}
    void setScale(float scale);
    void setAnchor(Anchor anchor){anchor_ = anchor;}
    Anchor getAnchor() const {return anchor_;}
    
};
