#ifndef GAME_HPP
#define GAME_HPP

#include "../../core/include/scene_manager.hpp"
#include "../../core/include/standard_type.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace project
{
class game
{
public:
    game(standard_type::int32 w, standard_type::int32 h, standard_type::int32 fps) : aspect_numerator(w), aspect_denominator(h), max_fps(fps) {}
    void play();

private:
    void      init();
    void      control();
    void      update(double delta_time);
    void      render();
    void      quit();
    SDL_FRect get_final_rect(float window_width, float window_height);
    bool      exit_flag{false};
    bool      is_full_screen{false};
    SDL_Window(*win) { nullptr };
    SDL_Renderer(*renderer) { nullptr };
    SDL_Texture(*final_texture) { nullptr };
    scene_manager        scene_manager;
    standard_type::int32 logic_width;
    standard_type::int32 logic_height;
    standard_type::int32 aspect_numerator;
    standard_type::int32 aspect_denominator;
    standard_type::int32 max_fps;
    standard_type::int32 current_fps;
    float                min_frame_time;
};
} // namespace project

#endif