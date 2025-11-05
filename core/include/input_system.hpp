#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include "standard_type.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <unordered_map>

namespace project
{
class input_system
{
public:
    input_system(const input_system &)            = delete;
    input_system &operator=(const input_system &) = delete;
    input_system(input_system &&)                 = delete;
    input_system &operator=(input_system &&)      = delete;

    static input_system &instance();

    void sync();
    void process_event(const SDL_Event &e);
    bool is_key_pressed(SDL_Scancode key) const;
    bool is_key_down(SDL_Scancode key) const;
    bool is_key_released(SDL_Scancode key) const;

    bool       is_mouse_pressed(standard_type::uint8 button) const;
    bool       is_mouse_down(standard_type::uint8 button) const;
    bool       is_mouse_released(standard_type::uint8 button) const;
    SDL_FPoint get_mouse_position() const { return m_mousePos; }

private:
    input_system()  = default;
    ~input_system() = default;

private:
    std::unordered_map<SDL_Scancode, bool> m_currentKeys;
    std::unordered_map<SDL_Scancode, bool> m_previousKeys;

    std::unordered_map<standard_type::uint8, bool> m_currentMouse;
    std::unordered_map<standard_type::uint8, bool> m_previousMouse;

    SDL_FPoint m_mousePos;
};
} // namespace project

#endif