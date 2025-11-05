#include "animation.hpp"
#include "game_object.hpp"
namespace project
{
class trap : public game_object
{
public:
    trap() = default;
    void init() override;
    void update(float delta_time) override;
    void render(SDL_Renderer *renderer, const camera &camera) override;
    void on_collision(game_object *other, float delta_time) override;

private:
    std::unique_ptr<animation> trap_animation;
};
} // namespace project
