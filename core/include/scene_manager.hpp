#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "scene.hpp"
#include <SDL3/SDL_render.h>
#include <memory>

namespace project
{
class scene_manager
{
public:
    void set_renderer(SDL_Renderer *renderer);
    void change_scene(std::unique_ptr<scene> new_scene);
    void update(float delta_time);
    void render();

private:
    SDL_Renderer          *m_renderer;
    std::unique_ptr<scene> current_scene;
};
} // namespace project

#endif