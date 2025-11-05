#include "../include/game.hpp"
#include "../include/constant.hpp"
#include "../include/input_system.hpp"
#include "../include/resource_manager.hpp"
#include "../include/sdl_wrapped.hpp"
#include "../include/test_scene.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <algorithm>

using namespace project;

void game::init()
{
    logic_width    = aspect_numerator * 80;
    logic_height   = aspect_denominator * 80;
    min_frame_time = 1e9 / max_fps;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    win           = SDL_CreateWindow(window_name, logic_width, logic_height, SDL_WINDOW_RESIZABLE);
    renderer      = SDL_CreateRenderer(win, nullptr);
    final_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
    resource_manager::instance().load(renderer, "assets");
    scene_manager.set_renderer(renderer);
    scene_manager.change_scene(std::make_unique<test_scene>());
    return;
}

void game::control()
{
    input_system::instance().sync();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            exit_flag = true;
            break;
        default:
            input_system::instance().process_event(event);
            break;
        }
    }
    if (input_system::instance().is_key_pressed(SDL_SCANCODE_F12))
    {
        is_full_screen = !is_full_screen;
        SDL_SetWindowFullscreen(win, is_full_screen);
    }
    if constexpr (RELEASE)
        return;
    if (input_system::instance().is_key_pressed(SDL_SCANCODE_F2))
    {
        is_debug_mode_open = !is_debug_mode_open;
    }
}

SDL_FRect game::get_final_rect(float window_width, float window_height)
{
    float factor{std::min(static_cast<float>(window_width) / aspect_numerator, static_cast<float>(window_height) / aspect_denominator)};
    float final_width{aspect_numerator * factor};
    float final_height{aspect_denominator * factor};
    float final_x{(window_width - final_width) / 2};
    float final_y{(window_height - final_height) / 2};
    return {final_x, final_y, final_width, final_height};
}

void game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, final_texture);
    SDL_RenderClear(renderer);
    scene_manager.render();
    SDL_Color   textColor   = {255, 255, 255, 255};
    std::string text        = "fps : " + std::to_string(current_fps);
    auto        textSurface = TTF_RenderText_Blended(resource_manager::instance().get_font("misans"), text.c_str(), text.length(), textColor);
    auto        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    SDL_FRect f{10, 0, 100, 40};
    SDL_RenderTexture(renderer, textTexture, nullptr, &f);
    SDL_SetRenderTarget(renderer, nullptr);
    standard_type::int32 actual_width, actual_height;
    SDL_GetWindowSize(win, &actual_width, &actual_height);
    SDL_FRect &&final_rect{get_final_rect(actual_width, actual_height)};
    SDL_RenderTexture(renderer, final_texture, nullptr, &final_rect);
    SDL_RenderPresent(renderer);
    return;
}

void game::update(double delta_time)
{
    scene_manager.update(delta_time);
    current_fps = 1e9 / delta_time;
    return;
}

void game::quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return;
}

void game::play()
{
    init();
    standard_type::uint64 last_time  = SDL_GetPerformanceCounter();
    standard_type::uint64 delta_time = 0;
    while (!exit_flag)
    {
        standard_type::uint64 frame_start = SDL_GetPerformanceCounter();
        delta_time                        = (frame_start - last_time) * 1e9 / SDL_GetPerformanceFrequency();
        last_time                         = frame_start;
        delta_time                        = std::min(static_cast<standard_type::uint64>(1e9), delta_time);
        control();
        update(delta_time);
        render();
        standard_type::uint64 frame_end  = SDL_GetPerformanceCounter();
        standard_type::uint64 elapsed_ns = (frame_end - frame_start) * 1e9 / SDL_GetPerformanceFrequency();

        if (elapsed_ns < min_frame_time)
        {
            Uint32 delay_ms = static_cast<Uint32>((min_frame_time - elapsed_ns) / 1e6);
            if (delay_ms > 0)
            {
                SDL_Delay(delay_ms);
            }
        }
    }
    quit();
}