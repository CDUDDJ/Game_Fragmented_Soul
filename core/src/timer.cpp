#include "../include/timer.hpp"

using namespace project;

void timer::update(float delta_time)
{
    if (has_invoked)
    {
        return;
    }
    current += delta_time;
    if (current >= target)
    {
        if (callback != nullptr)
        {
            callback();
        }
        has_invoked = true;
    }
}

void timer::set_callback(const std::function<void()> &func)
{
    callback = func;
}

void timer::set_time(float nanosecond)
{
    target = nanosecond;
}

void timer::start()
{
    has_invoked = false;
    current     = 0;
}

void timer::start(const std::function<void()> &func)
{
    func();
    start();
}