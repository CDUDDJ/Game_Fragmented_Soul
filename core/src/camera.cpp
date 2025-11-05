#include "../include/camera.hpp"
#include "../include/game_object.hpp"
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace project;

camera::camera(float win_w, float win_h, float world_w, float world_h)
{
    window_width  = win_w;
    window_height = win_h;
    world_width   = world_w;
    world_height  = world_h;
    auto gcd{std::gcd(static_cast<standard_type::int32>(window_width), static_cast<standard_type::int32>(window_height))};
    if (world_width / gcd >= world_height / gcd)
    {
        src_width  = world_height * window_width / window_height;
        src_height = world_height;
    }
    else
    {
        src_height = world_width * window_height / window_width;
        src_width  = world_width;
    }
    scale = window_width / src_width;
}

void camera::set_position(float x, float y)
{
    this->x = x;
    this->y = y;
}

void camera::start_shake(standard_type::uint64 duration_ns, float intensity, float frequency)
{
    shaking            = true;
    shake_duration_ns  = duration_ns;
    shake_time_left_ns = duration_ns;
    shake_intensity    = intensity;
    shake_frequency    = frequency;
    shake_elapsed      = 0.0;
}

void camera::update(standard_type::uint64 delta_time_ns)
{
    tar_x = std::clamp(binded_object->get_point().first - src_width / 2.0f, 0.0f, world_width - src_width);
    tar_y = std::clamp(binded_object->get_point().second - src_height / 2.0f, 0.0f, world_height - src_height);

    if (x != tar_x)
    {
        if (x < tar_x)
            x += (tar_x - x) * smooth_factor;
        else
            x -= (x - tar_x) * smooth_factor;
    }

    if (y != tar_y)
    {
        if (y < tar_y)
            y += (tar_y - y) * smooth_factor;
        else
            y -= (y - tar_y) * smooth_factor;
    }

    if (!shaking)
        return;

    if (shake_time_left_ns <= delta_time_ns)
    {
        shaking        = false;
        shake_offset_x = 0;
        shake_offset_y = 0;
        return;
    }

    shake_time_left_ns -= delta_time_ns;
    shake_elapsed += static_cast<double>(delta_time_ns) / 1e9;

    double decay = std::pow(static_cast<double>(shake_time_left_ns) / shake_duration_ns, 2.0);

    shake_offset_x = std::sin(shake_elapsed * shake_frequency * 2.0 * M_PI) * shake_intensity * decay;
    shake_offset_y = std::cos(shake_elapsed * shake_frequency * 2.0 * M_PI) * shake_intensity * decay;
}

void camera::bind(game_object *obj)
{
    binded_object = obj;
}

SDL_FRect camera::get_source_view() const
{
    return {x + shake_offset_x, y + shake_offset_y, src_width, src_height};
}

SDL_FRect camera::get_window_view() const
{
    return {0, 0, window_width, window_height};
}

bool camera::is_shaking() const
{
    return shaking;
}

SDL_FRect camera::to_window_view(const SDL_FRect &rect) const
{
    SDL_FRect src_view{get_source_view()};
    SDL_FRect dst_rect{get_window_view()};
    return {(rect.x - src_view.x) * scale + rect.w / 2, (rect.y - src_view.y) * scale + rect.h / 2, rect.w, rect.h};
}

float camera::get_scale() const
{
    return scale;
}