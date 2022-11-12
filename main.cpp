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

class GameModel : public stf::smv::BaseModel
{
public:

    GameBoard mBoard = GameBoard();
    Cursor mCursor = Cursor();
    std::vector<Note> log;
    stf::ColorTable player = stf::ColorTable::White;

    GameModel()
    {
        log.push_back({cells::emptyCell(), stf::ColorTable::Default, {0,0}, stf::ColorTable::Default, {0,0}, TurnType::Nothing});
    }

    void pieceMoveProc()
    {
        mBoard.place(mCursor.selectableCell.pos, mCursor.selectedCell.cell);
        mBoard.clear(mCursor.selectedCell.pos);
    }

    void castlingProc(CastlingKing *king, const stf::Vec2d& kingDPos, const int rookSX, const int rookDX)
    {
        mBoard.clear({rookSX, king->y()});
        mBoard.clear(king->uniquePos());

        mBoard.place(kingDPos,                         king->getKing());
        mBoard.place(kingDPos + stf::Vec2d(rookDX, 0), king->getRook());
    }

    TurnType findCastlingTurn(CastlingKing *king)
    {
        if(mCursor.selectedCell.cell->view() != King().view())
            return TurnType::Nothing;

        if(mCursor.selectableCell.pos == king->longCastlingPos() && king->isLongCastlingPossible(mBoard, log)) {
            castlingProc(king, king->longCastlingPos(), 0, +1);
            return TurnType::LeftCastling;
        }
        else if(mCursor.selectableCell.pos == king->shortCastlingPos() && king->isShortCastlingPossible(mBoard, log)) {
            castlingProc(king, king->shortCastlingPos(), 7, -1);
            return TurnType::RightCastling;
        }
        return TurnType::Nothing;
    }


    bool makeMove(const stf::Vec2d &selected, const stf::Vec2d &selectable)
    {
        GameBoard gb = mBoard;
        BoardCell *dest = gb[selectable];
        BoardCell *cell = gb[selected];

        if(cell->canAttack(gb, selected, selectable)) {
            gb.place(selectable, cell);
            gb.clear(selected);
        }
        if(cell->canJump(gb, selected, selectable)) {
            gb.place(selectable, cell);
            gb.clear(selected);
        }

        TurnType bIsCheckW = gb.blackCheckToWhite();
        TurnType wIsCheckB = gb.whiteCheckToBlack();

        if((bIsCheckW == TurnType::BCheckToW) || (wIsCheckB == TurnType::WCheckToB)) {
            return false;
        }
        return true;
    }

    bool isCheckmate()
    {
        for(int cy = 0; cy < mBoard.Size.y; ++cy) {
            for(int cx = 0; cx < mBoard.Size.x; ++cx) {
                for(int dy = 0; dy < mBoard.Size.y; ++dy) {
                    for(int dx = 0; dx < mBoard.Size.x; ++dx) {
                        if(mBoard[{cx,cy}]->color() != player)
                            continue;
                        if(stf::Vec2d{cx,cy} == stf::Vec2d{dx,dy})
                            continue;
                        if(makeMove({cx,cy}, {dx,dy}))
                            return true;
                    }
                }
            }
        }
        return false;
    }

    stf::smv::IView *put(stf::smv::IView *sender)
    {
        if(!isCheckmate())
            stf::Renderer::log<<stf::endl<<"Checkmate!";
//            exit(0);
        else if(mCursor.selectedCell.cell == cells::emptyCell() && mBoard[mCursor.selectableCell.pos]->color() == player)
        {
            mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
        }
        else if(mCursor.selectableCell.pos.x != mCursor.selectedCell.pos.x || mCursor.selectableCell.pos.y != mCursor.selectedCell.pos.y)
        {
            TurnType turn = TurnType::Nothing;
            CastlingKing *king = dynamic_cast<CastlingKing*>(mCursor.selectedCell.cell);

            BoardCell *dest = mBoard[mCursor.selectableCell.pos];
            BoardCell *cell = mCursor.selectedCell.cell;

            stf::Vec2d selected = mCursor.selectedCell.pos;
            stf::Vec2d selectable = mCursor.selectableCell.pos;

            turn = findCastlingTurn(king);

            if(cell->canAttack(mBoard, selected, selectable)) {
                pieceMoveProc();
                turn = TurnType::Attack;
            } else if(cell->canJump(mBoard, selected, selectable)) {
                pieceMoveProc();
                turn = TurnType::Move;
            }

            mBoard.transformPawns();

            TurnType bIsCheckW = mBoard.blackCheckToWhite();
            if(bIsCheckW == TurnType::BCheckToW) stf::Renderer::log << stf::endl << "Black check to the white!";
            TurnType wIsCheckB = mBoard.whiteCheckToBlack();
            if(wIsCheckB == TurnType::WCheckToB) stf::Renderer::log << stf::endl << "White check to the black!";

            if((bIsCheckW == TurnType::BCheckToW && player == stf::ColorTable::White) || (wIsCheckB == TurnType::WCheckToB && player == stf::ColorTable::Red)) {
                stf::Renderer::log<<stf::endl<<"UNRESOLVED";

                mBoard.place(selected, cell);
                mBoard.place(selectable, dest);

                return sender;
            }

            if(turn != TurnType::Nothing)
                log.push_back({ mCursor.selectedCell.cell,
                                player,
                                mCursor.selectedCell.pos,
                                player == stf::ColorTable::Red ? stf::ColorTable::White : stf::ColorTable::Red,
                                mCursor.selectableCell.pos,
                                turn });


            stf::Renderer::log << stf::endl <<
                                  log.back().cell->uniqueView() << " from " <<
                                  log.back().from << " to " <<
                                  log.back().to << " " <<
                                  static_cast<uint8_t>(log.back().type);
            mCursor.reset();
            if(turn != TurnType::Nothing && turn != TurnType::Unresolved)
                player = player == stf::ColorTable::White ? stf::ColorTable::Red : stf::ColorTable::White;
        }

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

        renderer.drawPixel({0,12}, gm->player == stf::ColorTable::Red ? 'B' : 'W');
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

    bool onUpdate(const float dt) final
    {
        currentView->show(renderer);
        currentView->update(dt);
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
