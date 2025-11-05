#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include "collision_box.hpp"
#include "constant.hpp"
#include "sdl_wrapped.hpp"
#include <SDL3/SDL_log.h>
#include <functional>
#include <vector>

namespace project
{
template <typename object>
class collision_manager
{
    static_assert(std::is_enum_v<object>, "object must be an enum");

public:
    collision_manager()  = default;
    ~collision_manager() = default;
    void add_collision_box(game_object *obj, object src, standard_type::uint32 tar, const std::function<void(float)> &func, camera *camera, float x = 0, float y = 0, float w = 0, float h = 0)
    {
        collision_box<object> box;
        box.bind_obj    = obj;
        box.bind_camera = camera;
        box.src         = src;
        box.tar         = tar;
        box.margin      = {x, y, w, h};
        box.callback    = func;
        box.is_enable   = true;
        boxs.emplace_back(std::move(box));
    }
    void update(float delta_time)
    {
        for (standard_type::uint64 i = 0; i < boxs.size(); ++i)
        {
            for (standard_type::uint64 j = i + 1; j < boxs.size(); ++j)
            {
                if (boxs[i].invoked(boxs[j]))
                {
                    boxs[i].callback(delta_time);
                    boxs[j].callback(delta_time);
                }
            }
        }
    }
    void render(SDL_Renderer *renderer, const camera &camera)
    {
        if constexpr (RELEASE)
            return;
        for (const auto &item : boxs)
        {
            if (!item.is_enable)
                continue;
            auto view{item.get_rect()};
            render_rect(renderer, camera.to_window_view(view), {0, 0, 255, 255});
        }
    }

private:
    std::vector<collision_box<object>> boxs;
};
} // namespace project

#endif