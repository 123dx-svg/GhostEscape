#include "Timer.h"

Timer* Timer::addTimerChild(Object* parent, float interval)
{
    Timer* timer = new Timer();
    timer->setInterval(interval);
    if (parent)parent->addChild(timer);
    timer->setActive(false);
    return timer;
}

void Timer::update(float deltaTime)
{
    Object::update(deltaTime);
    timer_ += deltaTime;
    if (timer_ >= interval_)
    {
        timer_ = 0.0f;
        timeOut_ = true;
    }
}

bool Timer::timeOut()
{
    if (timeOut_)
    {
        timeOut_ = false;
        return true;
    }
    return false;
}
