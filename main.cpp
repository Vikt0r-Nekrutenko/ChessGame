#include <window.hpp>
#include <iostream>
#include "gameboard.hpp"
#include "imodel.hpp"
#include "iview.hpp"


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

struct Note
{
    BoardCell *cell;
    stf::Vec2d from;
    stf::Vec2d to;
};

class GameModel : public stf::smv::BaseModel
{
public:

    GameBoard mBoard = GameBoard();
    Cursor mCursor = Cursor();
    std::vector<Note> log;

    stf::smv::IView *put(stf::smv::IView *sender)
    {
        if(mCursor.selectedCell.cell == cells::emptyCell())
        {
            mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
        }
        else
        {
            stf::Vec2d kingCastlingPos = {std::abs((mCursor.selectableCell.pos - mCursor.selectedCell.pos).x), std::abs((mCursor.selectableCell.pos - mCursor.selectedCell.pos).y)};
            uint8_t kingView = mBoard[{mCursor.selectedCell.pos}]->view();


            if(kingView == King().view() && kingCastlingPos == stf::Vec2d{2,0})
            {
                stf::Vec2d kingPos  = stf::Vec2d(4,mCursor.selectedCell.pos.y);

                stf::Vec2d lRookPos = stf::Vec2d(0,mCursor.selectedCell.pos.y);
                stf::Vec2d lRookDes = stf::Vec2d(mCursor.selectableCell.pos.x + 1,mCursor.selectedCell.pos.y);

                stf::Vec2d rRookPos = stf::Vec2d(7,mCursor.selectedCell.pos.y);
                stf::Vec2d rRookDes = stf::Vec2d(mCursor.selectableCell.pos.x - 1,mCursor.selectedCell.pos.y);

                if(mBoard[kingPos]->noPiecesOnWay(mBoard, kingPos, mCursor.selectableCell.pos)){
                    if(mBoard[lRookPos]->noPiecesOnWay(mBoard, lRookPos, lRookDes)) {
                        bool ex = true;
                        for(auto i : log) {
                            if(i.from == lRookPos)
                                ex = false;
                        }
                        if(ex)
                            stf::Renderer::log << stf::endl << "L!!!" << stf::endl;
                    }
                    else if(mBoard[rRookPos]->noPiecesOnWay(mBoard, rRookPos, rRookDes)){
                        bool ex = true;
                        for(auto i : log) {
                            if(i.from == rRookPos)
                                ex = false;
                        }
                        if(ex)
                            stf::Renderer::log << stf::endl << "R!!!" << stf::endl;
                    }
                }
            }
            if(mCursor.selectedCell.cell->canJump(mBoard, mCursor.selectedCell.pos, mCursor.selectableCell.pos) ||
               mCursor.selectedCell.cell->canAttack(mBoard, mCursor.selectedCell.pos, mCursor.selectableCell.pos))
            {
                log.push_back({ mCursor.selectedCell.cell, mCursor.selectedCell.pos, mCursor.selectableCell.pos });
                stf::Renderer::log << stf::endl << log.back().cell->uniqueView() << " from " << log.back().from << " to " << log.back().to << stf::endl;

                mBoard.isCheck(stf::ColorTable::Black);
                if(mBoard.isCheckmate(mCursor.selectableCell.pos, stf::ColorTable::Black))
                    stf::Renderer::log << stf::endl << "CHECKMATE";

                mBoard.place(mCursor.selectableCell.pos, mCursor.selectedCell.cell);
                mBoard.clear(mCursor.selectedCell.pos);
                mCursor.reset();
            }
        }

        mBoard.transformPawns();

        return sender;
    }

    stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) override
    {
        switch (key)
            {
            case 'w':
                if(mCursor.selectableCell.pos.y > 0)
                    mCursor.selectableCell.pos.y -= 1;
                else
                    mCursor.selectableCell.pos.y = mBoard.Size.y - 1;
                break;

            case 'a':
                if(mCursor.selectableCell.pos.x > 0)
                    mCursor.selectableCell.pos.x -= 1;
                else
                    mCursor.selectableCell.pos.x = mBoard.Size.x - 1;
                break;

            case 's':
                if(mCursor.selectableCell.pos.y < mBoard.Size.y-1)
                    mCursor.selectableCell.pos.y += 1;
                else
                    mCursor.selectableCell.pos.y = 0;
                break;

            case 'd':
                if(mCursor.selectableCell.pos.x < mBoard.Size.x-1)
                    mCursor.selectableCell.pos.x += 1;
                else
                    mCursor.selectableCell.pos.x = 0;
                break;

            case 'q':
                mCursor.reset();
                break;

            case ' ':
                return put(sender);
            }
            return sender;
    }
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
                renderer.drawPixel({x * 2 + 1, y + 2},
                        gm->mBoard[{x,y}]->view()==' '?'.':gm->mBoard[{x,y}]->view(),
                        gm->mBoard[{x,y}]->color());
            }
        }
        if(gm->mCursor.selectedCell.cell != cells::emptyCell())
        {
            renderer.drawPixel({gm->mCursor.selectedCell.pos.x * 2,     gm->mCursor.selectedCell.pos.y + 2}, '(');
            renderer.drawPixel({gm->mCursor.selectedCell.pos.x * 2 + 2, gm->mCursor.selectedCell.pos.y + 2}, ')');
        }
        renderer.drawPixel({gm->mCursor.selectableCell.pos.x * 2,     gm->mCursor.selectableCell.pos.y + 2}, '[');
        renderer.drawPixel({gm->mCursor.selectableCell.pos.x * 2 + 2, gm->mCursor.selectableCell.pos.y + 2}, ']');
    }
};

class Game : public stf::Window
{
public:
    GameModel gm = GameModel();
    GameView gv = GameView(&gm);
    stf::smv::IView *currentView = &gv;

    Game()
    {
        enableLog();
        stf::Renderer::log.setHeight(20);
        stf::Renderer::log.setX(30);
    }

    bool onUpdate(const float) final
    {
        currentView->show(renderer);
        return true;
    }

    void keyEvents(const int key) final
    {
        currentView->keyEventsHandler(key);
    }

    void mouseEvents(const stf::MouseRecord& mr) final
    {

    }
};

int main()
{
    return Game().run();
}
