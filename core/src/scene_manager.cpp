#include "../include/scene_manager.hpp"

using namespace project;

void scene_manager::set_renderer(SDL_Renderer *renderer)
{
    m_renderer = renderer;
}

void scene_manager::change_scene(std::unique_ptr<scene> new_scene)
{
    current_scene = std::move(new_scene);
    current_scene->init();
}

void scene_manager::update(float delta_time)
{
    current_scene->update(delta_time);
}

void scene_manager::render()
{
    current_scene->render(m_renderer);
}