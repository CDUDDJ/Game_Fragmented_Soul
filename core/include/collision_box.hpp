#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include "camera.hpp"
#include "game_object.hpp"
#include <SDL3/SDL_rect.h>
#include <functional>
#include <type_traits>

namespace project
{
template <typename object>
struct collision_box
{
    static_assert(std::is_enum_v<object>, "object must be an enum");

public:
    collision_box()  = default;
    ~collision_box() = default;
    bool invoked(const collision_box<object> &b)
    {
        if (!this->is_enable || !b.is_enable)
            return false;
        auto rect_a{bind_camera->to_window_view(this->get_rect())};
        auto rect_b{bind_camera->to_window_view(b.get_rect())};
        if (static_cast<standard_type::uint32>(this->src) and static_cast<standard_type::uint32>(b.tar) == 0 ||
            static_cast<standard_type::uint32>(this->tar) and static_cast<standard_type::uint32>(b.src) == 0)
            return false;
        if (SDL_HasRectIntersectionFloat(&rect_a, &rect_b))
            return true;
        return false;
    }
    SDL_FRect                  margin{0, 0, 0, 0};
    object                     src;
    standard_type::uint32      tar;
    bool                       is_enable{true};
    game_object               *bind_obj{nullptr};
    camera                    *bind_camera{nullptr};
    std::function<void(float)> callback{nullptr};
    SDL_FRect                  get_rect() const
    {
        auto rect{bind_obj->get_rect()};
        return {rect.x + margin.x, rect.y + margin.y, rect.w - margin.w, rect.h - margin.h};
    }
};
} // namespace project

#endif