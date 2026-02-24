#include <sgf/sgf.hpp>

using namespace sgf;

class game : public kernel<game>
{
public:
    game() : kernel("残魂", {1280, 720}, {1280, 720}, 0)
    {
    }

    void on_input(kernel<game> &k, const sgf::input_event &e)
    {
    }

    void on_update(kernel<game> &k, const sgf::frame_context &ctx)
    {
    }

    void on_render(kernel<game> &k)
    {
    }
};

int main()
{
    game{}.run();
}