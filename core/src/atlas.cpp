#include "../include/atlas.hpp"
#include "../include/resource_manager.hpp"

using namespace project;

atlas::atlas(std::string_view source_key, standard_type::uint32 frames, standard_type::int8 mutiply, flip_diretion direction)
{
    this->source_key = source_key;
    texture          = resource_manager::instance().get_texture(this->source_key);
    float width, height;
    SDL_GetTextureSize(texture, &width, &height);
    float start_x{0}, start_y{0};
    float each_width, each_height;
    if (direction == flip_diretion::horizontal)
    {
        each_width  = width / frames;
        each_height = height;
        while (start_x < width - (each_width / 2))
        {
            frects.emplace_back(SDL_FRect{start_x, 0, each_width, each_height});
            start_x += each_width;
        }
    }
    else
    {
        each_width  = width;
        each_height = height / frames;
        while (start_y < height - (each_height / 2))
        {
            frects.emplace_back(SDL_FRect{0, start_y, each_width, each_height});
            start_y += each_height;
        }
    }
    frame_width  = each_width * mutiply;
    frame_height = each_height * mutiply;
}

std::string_view atlas::get_source_key()
{
    return source_key;
}

SDL_FRect atlas::get_next_frect()
{
    ++index;
    if (index >= frects.size())
    {
        index = 0;
    }
    return frects[index];
}

float atlas::get_frame_width()
{
    return frame_width;
}

float atlas::get_frame_height()
{
    return frame_height;
}