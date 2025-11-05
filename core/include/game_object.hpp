#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "camera.hpp"
#include "standard_type.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

namespace project
{
class game_object
{
public:
    enum class direction
    {
        horizon,
        vertical,
        center
    };
    game_object()          = default;
    virtual ~game_object() = default;
    inline standard_type::point get_point() const
    {
        return {rect.x, rect.y};
    }
    inline SDL_FRect get_rect() const
    {
        return rect;
    }
    virtual void init()                                               = 0;
    virtual void update(float delta_time)                             = 0;
    virtual void render(SDL_Renderer *renderer, const camera &camera) = 0;
    virtual void on_collision(game_object *other, float delta_time)   = 0;

protected:
    SDL_FRect rect{0, 0, 0, 0};
};
} // namespace project

#endif