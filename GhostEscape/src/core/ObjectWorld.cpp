#include "ObjectWorld.h"

#include "Scene.h"

void ObjectWorld::init()
{
    ObjectScreen::init();
    type_ = ObjectType::OBJECT_WORLD;
}

void ObjectWorld::update(float deltaTime)
{
    ObjectScreen::update(deltaTime);
    //render_position = Game::getInstance().getCurrentScene()->worldToScreen(position_);不需要每帧更新渲染坐标
}

void ObjectWorld::setPosition(const glm::vec2& position)
{
    position_ = position;
    render_position = Game::getInstance().getCurrentScene()->worldToScreen(position);
}

void ObjectWorld::setRenderPosition(const glm::vec2& pos)
{
    ObjectScreen::setRenderPosition(pos);
    position_ = Game::getInstance().getCurrentScene()->screenToWorld(pos);
}

glm::vec2 ObjectWorld::getRenderPosition()
{
    //用到时再计算渲染坐标
    return  Game::getInstance().getCurrentScene()->worldToScreen(position_);
}
