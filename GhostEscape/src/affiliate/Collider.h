#pragma once
#include "../core/ObjectAffiliate.h"

class Spell;
class Collider : public ObjectAffiliate
{
protected:
    friend class Spell;
    enum class Type
    {
        Circle,   //size_ 的x轴为直径 默认y=x
        Rectangle
    };
    Type type_ = Type::Circle;
public:
    static Collider* addColliderChild(ObjectScreen* parent,glm::vec2 size, Type type = Type::Circle , Anchor anchor = Anchor::CENTER);
    void render() override;
    bool isColliding(Collider* other) ;
    //get set
    Type getType() const {return type_;}
    void setType(Type type) {type_ = type;}
};
