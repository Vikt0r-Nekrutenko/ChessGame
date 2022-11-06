#include <window.hpp>
#include <iostream>
#include "pawns.hpp"
#include "imodel.hpp"
#include "iview.hpp"

class GameBoard
{
public:

    const stf::Vec2d Size { 8, 8 };

    GameBoard()
    {
        for(int i = 0; i < Size.x * Size.y; ++i) {
            mBoard.push_back(cells::emptyCell());
        }
    }

    BoardCell* operator[](const stf::Vec2d& pos) const
    {
        return mBoard.at(Size.x * pos.y + pos.x);
    }

    std::vector<BoardCell *> mBoard;
};

struct Selector
{
    stf::Vec2d pos = stf::Vec2d( 0, 0 );
    BoardCell *cell = cells::emptyCell();
};

struct Cursor
{
    Selector selectableCell;
    Selector selectedCell;

    void reset()
    {
        selectedCell.cell = selectableCell.cell = cells::emptyCell();
    }

    void select(BoardCell *cell)
    {
        selectedCell.pos = selectableCell.pos;
        selectedCell.cell = selectableCell.cell = cell;
    }
};

class GameModel : public stf::smv::BaseModel
{
public:

    GameBoard mBoard;
};

class GameView : public stf::smv::IView
{
public:
    GameView(GameModel *model) : stf::smv::IView(model) {}

    void show(stf::Renderer &renderer) override
    {
        GameModel *gm = static_cast<GameModel*>(m_model);

        for(int y = 0; y < gm->mBoard.Size.y; ++y) {
            for(int x = 0; x < gm->mBoard.Size.y; ++x) {
                renderer.drawPixel({x * 2 + 1, y + 2}, gm->mBoard[{x,y}]->view()==' '?'.':gm->mBoard[{x,y}]->view(), gm->mBoard[{x,y}]->color());
            }
        }
    }
};

class Game : public stf::Window
{
    GameModel gm = GameModel();
    GameView gv = GameView(&gm);
    stf::smv::IView *currentView = &gv;

    bool onUpdate(const float) final
    {
        currentView->show(renderer);
        return true;
    }

    void keyEvents(const int key) final
    {

    }

    void mouseEvents(const stf::MouseRecord& mr) final
    {

    }
};

int main()
{
    return Game().run();
}
