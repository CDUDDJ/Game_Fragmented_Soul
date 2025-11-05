#ifndef FSM_HPP
#define FSM_HPP

#include <SDL3/SDL_log.h>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace project
{
namespace fsm_detail
{
template <typename E>
struct EnumHash
{
    static_assert(std::is_enum_v<E>, "EnumHash requires enum type");
    std::size_t operator()(E e) const noexcept
    {
        using UT = std::underlying_type_t<E>;
        return std::hash<UT>{}(static_cast<UT>(e));
    }
};

template <typename E>
struct PairHash
{
    std::size_t operator()(const std::pair<E, E> &p) const noexcept
    {
        EnumHash<E> h;
        std::size_t a = h(p.first);
        std::size_t b = h(p.second);
        return a ^ (b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2));
    }
};
} // namespace fsm_detail

template <typename State>
class FSM
{
    static_assert(std::is_enum_v<State>, "FSM<State> requires State to be an enum type (use enum class).");

public:
    using Action = std::function<void()>;
    using Guard  = std::function<bool()>;

    explicit FSM(State initial) : current_(initial) {}

    State current() const noexcept { return current_; }

    void set_on_enter(State s, Action a)
    {
        on_enter_[s] = std::move(a);
    }
    void set_on_exit(State s, Action a)
    {
        on_exit_[s] = std::move(a);
    }

    void add_transition(State from, State to, Action action = nullptr, Guard guard = nullptr)
    {
        transitions_[{from, to}] = Transition{std::move(action), std::move(guard)};
    }

    bool can_transition_to(State to) const
    {
        auto it = transitions_.find({current_, to});
        if (it == transitions_.end())
            return false;
        const Guard &g = it->second.guard;
        return !g || g();
    }

    void transition_to(State to)
    {
        auto it = transitions_.find({current_, to});
        if (it == transitions_.end())
        {
            SDL_Log("No transition registered from current state to target state");
            return;
        }
        const Transition &t = it->second;
        if (t.guard && !t.guard())
        {
            SDL_Log("Guard condition failed; transition not allowed");
            return;
        }
        auto it_exit = on_exit_.find(current_);
        if (it_exit != on_exit_.end() && it_exit->second)
            it_exit->second();

        if (t.action)
            t.action();

        current_ = to;

        auto it_enter = on_enter_.find(current_);
        if (it_enter != on_enter_.end() && it_enter->second)
            it_enter->second();
    }

    bool try_transition_to(State to)
    {
        auto it = transitions_.find({current_, to});
        if (it == transitions_.end())
            return false;
        const Transition &t = it->second;
        if (t.guard && !t.guard())
            return false;

        if (auto it_exit = on_exit_.find(current_); it_exit != on_exit_.end() && it_exit->second)
            it_exit->second();
        if (t.action)
            t.action();
        current_ = to;
        if (auto it_enter = on_enter_.find(current_); it_enter != on_enter_.end() && it_enter->second)
            it_enter->second();
        return true;
    }

private:
    struct Transition
    {
        Action action;
        Guard  guard;
    };

    State                                                                                current_;
    std::unordered_map<State, Action, fsm_detail::EnumHash<State>>                       on_enter_;
    std::unordered_map<State, Action, fsm_detail::EnumHash<State>>                       on_exit_;
    std::unordered_map<std::pair<State, State>, Transition, fsm_detail::PairHash<State>> transitions_;
};
} // namespace project

#endif