#include "../include/test_scene.hpp"
#include "../include/resource_manager.hpp"
#include "../include/role.hpp"
#include "../include/trap.hpp"

using namespace project;

void test_scene::init()
{
    game_objects.emplace_back(std::make_unique<role>());
    game_objects.emplace_back(std::make_unique<trap>());
    test_camera.bind(game_objects[0].get());
    test_collision_manager.add_collision_box(game_objects[0].get(), collision::role, static_cast<standard_type::uint32>(collision::trap), [&](float delta_time)
                                             {
                                                 auto r{static_cast<role *>(game_objects[0].get())};
                                            r->on_collision(game_objects[1].get(), delta_time); }, &test_camera, 2.7, 2, 18, 8);
    test_collision_manager.add_collision_box(game_objects[1].get(), collision::trap, static_cast<standard_type::uint32>(collision::role), [&](float delta_time) {}, &test_camera, 2.7, 2, 18, 8);

    for (auto &item : game_objects)
    {
        item->init();
    }
    // test_camera.start_shake(time_tool::second_to_nanosecond(3), 8, 24);
}

void test_scene::update(float delta_time)
{
    test_timer.update(delta_time);
    for (auto &item : game_objects)
    {
        item->update(delta_time);
    }
    test_camera.update(delta_time);
    test_collision_manager.update(delta_time);
}

void test_scene::render(SDL_Renderer *renderer)
{
    SDL_FRect src_view = test_camera.get_source_view();
    SDL_FRect dst_rect = test_camera.get_window_view();
    render_texture(renderer, resource_manager::instance().get_texture("background"), src_view, dst_rect);
    test_collision_manager.render(renderer, test_camera);
    for (const auto &item : game_objects)
    {
        item->render(renderer, test_camera);
    }
}
