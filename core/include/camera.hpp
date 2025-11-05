#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "standard_type.hpp"
#include <SDL3/SDL_rect.h>

namespace project
{

class game_object;

class camera
{
public:
    camera(float vw, float vh, float ww, float wh);
    void      start_shake(standard_type::uint64 duration_ns, float intensity, float frequency);
    void      update(standard_type::uint64 delta_time_ns);
    void      set_position(float x, float y);
    void      bind(game_object *object);
    bool      is_shaking() const;
    float     get_scale() const;
    SDL_FRect get_source_view() const;
    SDL_FRect get_window_view() const;
    SDL_FRect to_window_view(const SDL_FRect &rect) const;

private:
    void  update_view();
    float smooth_factor{0.15f};
    float window_width{}, window_height{};
    float world_width{}, world_height{};
    float src_width{}, src_height{};
    float x{0}, y{0};
    float tar_x{0}, tar_y{0};
    float scale{1};

    bool                  shaking{false};
    standard_type::uint64 shake_duration_ns{0};
    standard_type::uint64 shake_time_left_ns{0};

    float  shake_intensity{0};
    float  shake_frequency{0};
    double shake_elapsed{0};

    float shake_offset_x{0};
    float shake_offset_y{0};

    game_object *binded_object{nullptr};
};
} // namespace project

#endif