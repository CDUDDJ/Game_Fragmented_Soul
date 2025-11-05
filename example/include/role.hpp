#include "FSM.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "timer.hpp"
#include "vector2.hpp"

namespace project
{
class role : public game_object
{
public:
    role() = default;
    void init() override;
    void update(float delta_time) override;
    void render(SDL_Renderer *renderer, const camera &camera) override;
    void on_collision(game_object *other, float delta_time) override;
    enum class statu
    {
        ldle,
        run,
        hurt
    };

private:
    void                       control();
    void                       collision_trap();
    std::unique_ptr<animation> role_animation;
    bool                       is_right{true};
    standard_type::int32       key_k_count;
    FSM<statu>                 fsm{statu::ldle};
    vector2<float>             speed{0, 0};
    timer                      hurt_timer;
};
} // namespace project
