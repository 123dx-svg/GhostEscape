#pragma once
#include "../core/Object.h"

class Timer : public Object //此类创建时默认active为false
{

protected:
    float timer_ = 0.0f;
    float interval_ = 3.0f;
    bool timeOut_ = false;
public:

    //定时器
    static Timer* addTimerChild(Object* parent, float interval = 3.0f);
    void update(float deltaTime) override;

    void start(){is_active_ = true;}
    void stop(){is_active_ = false;}
    bool timeOut();
    float getProgress(){return timer_/interval_;}

    //get set
    float getInterval() const {return interval_;}
    void setInterval(float interval) {interval_ = interval;}
    float getTimer() const {return timer_;}
    void setTimer(float timer) {timer_ = timer;}
};
