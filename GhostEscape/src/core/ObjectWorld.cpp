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
    render_position = Game::getInstance().getCurrentScene()->worldToScreen(position_);
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
