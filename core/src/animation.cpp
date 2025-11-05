#include "../include/animation.hpp"
#include "../include/resource_manager.hpp"
#include "../include/sdl_wrapped.hpp"

using namespace project;

animation::animation(std::unique_ptr<atlas> atlas)
{
    m_atlas = std::move(atlas);
}

void animation::render(SDL_Renderer *render, const SDL_FRect &window_view)
{
    auto source{m_atlas->get_next_frect()};
    render_texture(render, resource_manager::instance().get_texture(m_atlas->get_source_key()), source, window_view);
}

void animation::render_rotate(SDL_Renderer *render, const SDL_FRect &window_view)
{
    auto source{m_atlas->get_next_frect()};
    render_texture_rotate(render, resource_manager::instance().get_texture(m_atlas->get_source_key()), source, window_view);
}