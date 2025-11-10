#include "Scene.h"

bool Scene::handleEvent(SDL_Event& event)
{
    
    //顺序很重要
    for (auto& child : children_screen_)
    {
        if (child->getActive())
        {
            if (child->handleEvent(event)) return true;
        }
    }
    if (is_paused_) return false;
    Object::handleEvent(event);
    for (auto& child : children_world_)
    {
        if (child->getActive())
        {
            if (child->handleEvent(event)) return true;
        }
    }
    return false;
}

void Scene::update(float deltaTime)
{
    if (!is_paused_)
    {
        Object::update(deltaTime);
        for (auto it = children_world_.begin(); it != children_world_.end();)
        {
            auto child = *it;
            if (child->getNeedRemove())
            {
                it = children_world_.erase(it);
                child->clean();
                delete child;
                child = nullptr;
                //SDL_Log("Scene::update: deleting child \n");
            }
            else
            {
                if (child->getActive())
                {
                    child->update(deltaTime);
                }
            
                ++it;
            }
        }
    }

    for (auto it = children_screen_.begin(); it != children_screen_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_screen_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        }
        else
        {
            if (child->getActive())
            {
                child->update(deltaTime);
            }
            ++it;
        }
    }
}

void Scene::render()
{
    Object::render();
    for (auto& child : children_world_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
    for (auto& child : children_screen_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto& child : children_world_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_world_.clear();
    for (auto& child : children_screen_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_screen_.clear();
}

void Scene::addChild(Object* child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_SCREEN:
            children_screen_.push_back(dynamic_cast<ObjectScreen*>(child));
            break;
        case ObjectType::OBJECT_WORLD:
        case ObjectType::ENEMY:
            children_world_.push_back(dynamic_cast<ObjectWorld*>(child));
            break;
        default:
            children_.push_back(child);
            break;
    }
}

void Scene::removeChild(Object* child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_WORLD:
        case ObjectType::ENEMY:
            children_world_.erase(std::remove(children_world_.begin(),children_world_.end(),dynamic_cast<ObjectWorld*>(child)),
                                  children_world_.end());
            break;
        case ObjectType::OBJECT_SCREEN:
            children_screen_.erase(std::remove(children_screen_.begin(),children_screen_.end(),dynamic_cast<ObjectScreen*>(child)),
                                   children_screen_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(),children_.end(),child), children_.end());
            break;
    }
}


void Scene::setCameraPosition(const glm::vec2& pos)
{
    camera_position_ = pos;
    camera_position_ = glm::clamp(camera_position_,glm::vec2(-30),world_size_-Game::getInstance().getScreenSize()+glm::vec2(30));
    
}
