#include "../include/role.hpp"
#include "../include/input_system.hpp"
#include "../include/time_tool.hpp"
#include "../include/trap.hpp"
#include <SDL3/SDL_log.h>

using namespace project;

void role::init()
{
    rect.x         = 0;
    rect.y         = 80;
    rect.w         = 96;
    rect.h         = 96;
    role_animation = std::make_unique<animation>(std::make_unique<atlas>("frog_ldle", 11, 3));

    fsm.set_on_enter(statu::ldle, [&]()
                     {
                         role_animation = std::make_unique<animation>(std::make_unique<atlas>("frog_ldle", 11, 3));
                         speed          = {0, 0}; });
    fsm.set_on_enter(statu::run, [&]()
                     { role_animation = std::make_unique<animation>(std::make_unique<atlas>("frog_run", 12, 3)); });

    fsm.set_on_enter(statu::hurt, [&]()
                     { role_animation = std::make_unique<animation>(std::make_unique<atlas>("frog_hit", 7, 3)); });

    fsm.add_transition(statu::ldle, statu::run);
    fsm.add_transition(statu::run, statu::ldle);
    fsm.add_transition(statu::ldle, statu::hurt);
    fsm.add_transition(statu::run, statu::hurt);
    fsm.add_transition(statu::hurt, statu::ldle);
}

void role::control()
{
    if (input_system::instance().is_key_down(SDL_SCANCODE_D))
    {
        is_right = true;
        speed    = {50, 0};
        if (fsm.current() != statu::run)
        {
            if (fsm.can_transition_to(statu::run))
            {
                fsm.transition_to(statu::run);
            }
        }
    }
    else if (input_system::instance().is_key_down(SDL_SCANCODE_A))
    {
        is_right = false;
        speed    = {-50, 0};
        if (fsm.current() != statu::run)
        {
            if (fsm.can_transition_to(statu::run))
            {
                fsm.transition_to(statu::run);
            }
        }
    }
    else
    {
        if (fsm.current() == statu::run)
            fsm.transition_to(statu::ldle);
    }
}

void role::update(float delta_time)
{
    control();
    hurt_timer.update(delta_time);
    rect.x += time_tool::nanosecond_to_second(delta_time) * speed.get_x();
    rect.y += time_tool::nanosecond_to_second(delta_time) * speed.get_y();
}

void role::render(SDL_Renderer *renderer, const camera &camera)
{
    auto real_view{camera.to_window_view(get_rect())};
    if (is_right)
        role_animation->render(renderer, real_view);
    else
        role_animation->render_rotate(renderer, real_view);
}

void role::on_collision(game_object *other, float delta_time)
{
    if (auto t{dynamic_cast<trap *>(other)})
    {
        collision_trap();
    }
}

void role::collision_trap()
{
    if (fsm.can_transition_to(statu::hurt))
        fsm.transition_to(statu::hurt);
    hurt_timer.set_time(time_tool::second_to_nanosecond(0.1));
    hurt_timer.set_callback([&]()
                            { fsm.transition_to(statu::ldle); });
    hurt_timer.start();
}