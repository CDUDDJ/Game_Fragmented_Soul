#ifndef TIMER_HPP
#define TIMER_HPP

#include <functional>

namespace project
{
class timer
{
public:
    timer()  = default;
    ~timer() = default;
    void start();
    void start(const std::function<void()> &func);
    void update(float delta_time);
    void set_time(float nanosecond);
    void set_callback(const std::function<void()> &func);

private:
    float                 target{0};
    float                 current{0};
    bool                  has_invoked{false};
    std::function<void()> callback{nullptr};
};
} // namespace project

#endif