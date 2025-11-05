#ifndef ATLAS_HPP
#define ATLAS_HPP

#include "standard_type.hpp"
#include <SDL3/SDL_render.h>
#include <string>
#include <string_view>
#include <vector>

// 访问资源 获取资源的宽高参数 根据水平和竖直方向切分

class atlas
{
public:
    enum class flip_diretion
    {
        horizontal,
        vertical
    };
    atlas()  = delete;
    ~atlas() = default;
    atlas(std::string_view source_key, standard_type::uint32 frames, standard_type::int8 mutiply = 1, flip_diretion direction = atlas::flip_diretion::horizontal);
    std::string_view get_source_key();
    SDL_FRect        get_next_frect();
    float            get_frame_width();
    float            get_frame_height();

private:
    void                   size_multiply(standard_type::int8 x);
    SDL_Texture           *texture{nullptr};
    std::string            source_key;
    std::vector<SDL_FRect> frects;
    standard_type::int64   index{-1};
    float                  frame_width;
    float                  frame_height;
};

#endif