#include "../include/input_system.hpp"

using namespace project;

input_system &input_system::instance()
{
    static input_system instance;
    return instance;
}

void input_system::sync()
{
    m_previousKeys  = m_currentKeys;
    m_previousMouse = m_currentMouse;
}

void input_system::process_event(const SDL_Event &e)
{
    switch (e.type)
    {
    case SDL_EVENT_KEY_DOWN:
        m_currentKeys[e.key.scancode] = true;
        break;

    case SDL_EVENT_KEY_UP:
        m_currentKeys[e.key.scancode] = false;
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        m_currentMouse[e.button.button] = true;
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        m_currentMouse[e.button.button] = false;
        break;

    case SDL_EVENT_MOUSE_MOTION:
        m_mousePos.x = static_cast<float>(e.motion.x);
        m_mousePos.y = static_cast<float>(e.motion.y);
        break;

    default:
        break;
    }
}

bool input_system::is_key_pressed(SDL_Scancode key) const
{
    bool now  = m_currentKeys.count(key) ? m_currentKeys.at(key) : false;
    bool prev = m_previousKeys.count(key) ? m_previousKeys.at(key) : false;
    return now && !prev;
}

bool input_system::is_key_down(SDL_Scancode key) const
{
    return m_currentKeys.count(key) ? m_currentKeys.at(key) : false;
}

bool input_system::is_key_released(SDL_Scancode key) const
{
    bool now  = m_currentKeys.count(key) ? m_currentKeys.at(key) : false;
    bool prev = m_previousKeys.count(key) ? m_previousKeys.at(key) : false;
    return !now && prev;
}

bool input_system::is_mouse_pressed(standard_type::uint8 button) const
{
    bool now  = m_currentMouse.count(button) ? m_currentMouse.at(button) : false;
    bool prev = m_previousMouse.count(button) ? m_previousMouse.at(button) : false;
    return now && !prev;
}

bool input_system::is_mouse_down(standard_type::uint8 button) const
{
    return m_currentMouse.count(button) ? m_currentMouse.at(button) : false;
}

bool input_system::is_mouse_released(standard_type::uint8 button) const
{
    bool now  = m_currentMouse.count(button) ? m_currentMouse.at(button) : false;
    bool prev = m_previousMouse.count(button) ? m_previousMouse.at(button) : false;
    return !now && prev;
}
