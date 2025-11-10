#include "Collider.h"

Collider* Collider::addColliderChild(ObjectScreen* parent, glm::vec2 size, Type type,Anchor anchor)
{
    auto collider = new Collider();
    collider->setParent(parent);
    collider->setSize(size);
    collider->type_ = type;
    collider->setOffsetByAnchor(anchor);
    parent->addChild(collider);
    return collider;
}

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition()+offset_;
    Game::getInstance().renderFillCircle(pos,size_,0.3f);
#endif
}

bool Collider::isColliding(Collider* other)
{
    if (!other)return false;
    if (type_ == Type::Circle&&other->type_ == Type::Circle)//两个圆的情况
    {
        auto point1 = parent_->getPosition() + offset_ + size_/2.0f;
        auto point2 = other->parent_->getPosition() + offset_ + size_/2.0f;
        return glm::length(point1-point2) < (size_.x+other->size_.x)/2.0f;
    }
    //todo:添加矩形的情况
    return false;
}
