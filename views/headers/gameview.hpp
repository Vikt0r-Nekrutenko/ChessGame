#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class GameView : public IView
{
public:
    GameView(BaseModel *model, bool resetTheModel = false);
    ~GameView() override = default;

    IView* mouseEventsHandler(const stf::MouseRecord& mr) override;
    void show(Renderer &renderer) override;

private:
    Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
