#include "../include/resource_manager.hpp"
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <memory>

using namespace project;

resource_manager &resource_manager::instance()
{
    static std::unique_ptr<resource_manager, deleter> instance_ptr{new resource_manager()};
    return *instance_ptr;
}

void resource_manager::load(SDL_Renderer *render, const std::string path, const std::string base_path)
{
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            load(render, entry.path().string(), base_path + entry.path().filename().string() + '_');
        }
        else if (entry.is_regular_file())
        {
            if (entry.path().extension() == ".ttf")
            {
                font_map[base_path + entry.path().stem().string()] = TTF_OpenFont(entry.path().string().c_str(), 24);
            }
            else
            {
                texture_map[base_path + entry.path().stem().string()] = IMG_LoadTexture(render, entry.path().string().c_str());
            }
        }
    }
}

SDL_Texture *resource_manager::get_texture(std::string_view key)
{
    return texture_map[std::string{key}];
}

TTF_Font *resource_manager::get_font(std::string_view key)
{
    return font_map[std::string{key}];
}