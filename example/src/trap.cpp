#include "../include/trap.hpp"
#include "../include/time_tool.hpp"

using namespace project;

void trap::init()
{
    rect.x         = 700;
    rect.y         = 80;
    rect.w         = 96;
    rect.h         = 96;
    trap_animation = std::make_unique<animation>(std::make_unique<atlas>("guy_ldle", 11, 3));
}

void trap::update(float delta_time)
{
    rect.x -= 100 * time_tool::nanosecond_to_second(delta_time);
}

void trap::render(SDL_Renderer *renderer, const camera &camera)
{
    auto real_view{camera.to_window_view(get_rect())};
    trap_animation->render_rotate(renderer, real_view);
}

void trap::on_collision(game_object *other, float delta_time)
{
}