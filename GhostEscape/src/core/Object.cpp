#include "Object.h"

bool Object::handleEvent(SDL_Event& event)
{
    for (auto& child : children_)
    {
        if (child->getActive())
            if (child->handleEvent(event)) return true;
    }
    return false;
}

void Object::update(float deltaTime)
{

    //添加子对象 每轮先检查有没有要添加的东西
    for (auto& child : objectToAdd_)
    {
        addChild(child);
    }
    objectToAdd_.clear();

    
    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_.erase(it);
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

void Object::render()
{
    for (auto& child : children_)
    {
        if (child->getActive())
            child ->render();
    }
}

void Object::clean()
{
    for (auto& child : children_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_.clear();
}
