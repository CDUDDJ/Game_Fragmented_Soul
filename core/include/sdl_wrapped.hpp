#ifndef SDL_WRAPPED_HPP
#define SDL_WRAPPED_HPP

#include "constant.hpp"
#include "standard_type.hpp"
#include <SDL3/SDL_render.h>

namespace project
{
inline bool is_debug_mode_open = true;

inline void render_rect(SDL_Renderer *renderer, const SDL_FRect &dstrect, const standard_type::RGBA &rgba = {255, 127, 0, 255})
{
    if (!is_debug_mode_open)
        return;
    const auto &[r, g, b, a] = rgba;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderRect(renderer, &dstrect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
inline void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_FRect &srcrect, const SDL_FRect &dstrect)
{
    if constexpr (!RELEASE)
        render_rect(renderer, dstrect);
    SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
}
inline void render_texture_rotate(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_FRect &srcrect, const SDL_FRect &dstrect)
{
    if constexpr (!RELEASE)
        render_rect(renderer, dstrect);
    SDL_RenderTextureRotated(renderer, texture, &srcrect, &dstrect, 0, nullptr, SDL_FLIP_HORIZONTAL);
}
} // namespace project

#endif