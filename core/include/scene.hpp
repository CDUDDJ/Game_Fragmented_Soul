#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL3/SDL_render.h>

namespace project
{
class scene
{
public:
    virtual ~scene()                            = default;
    virtual void init()                         = 0;
    virtual void update(float delta_time)       = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};
} // namespace project

#endif