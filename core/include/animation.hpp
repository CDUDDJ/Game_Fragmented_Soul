#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "atlas.hpp"
#include <memory>

namespace project
{
class animation
{
public:
    animation()  = delete;
    ~animation() = default;
    animation(std::unique_ptr<atlas> atlas);
    void render(SDL_Renderer *render, const SDL_FRect &window_view);
    void render_rotate(SDL_Renderer *render, const SDL_FRect &window_view);

private:
    std::unique_ptr<atlas> m_atlas;
};
} // namespace project

#endif