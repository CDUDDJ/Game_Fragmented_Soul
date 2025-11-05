#pragma once

#include "camera.hpp"
#include "collision_manager.hpp"
#include "game_object.hpp"
#include "scene.hpp"
#include "timer.hpp"
#include <memory>

namespace project
{
class test_scene : public scene
{
public:
    void init() override;
    void update(float delta_time) override;
    void render(SDL_Renderer *renderer) override;
    enum class collision
    {
        null = 0,
        role = 1 << 0,
        trap = 1 << 1
    };

private:
    collision_manager<collision>              test_collision_manager;
    timer                                     test_timer;
    camera                                    test_camera{1280.0f, 720.0f, 1172.0f, 110.0f};
    std::vector<std::unique_ptr<game_object>> game_objects;
};
} // namespace project
