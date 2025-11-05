#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace project
{
class resource_manager
{
public:
    resource_manager(const resource_manager &)              = delete;
    resource_manager &operator=(const resource_manager &)   = delete;
    resource_manager(resource_manager &&)                   = delete;
    resource_manager        &operator=(resource_manager &&) = delete;
    static resource_manager &instance();
    void                     load(SDL_Renderer *render, const std::string path, const std::string base_path = "");
    SDL_Texture             *get_texture(std::string_view key);
    TTF_Font                *get_font(std::string_view key);

private:
    resource_manager()  = default;
    ~resource_manager() = default;
    struct deleter
    {
        void operator()(resource_manager *ptr) const { delete ptr; }
    };
    std::unordered_map<std::string, SDL_Texture *> texture_map;
    std::unordered_map<std::string, TTF_Font *>    font_map;
};
} // namespace project

#endif