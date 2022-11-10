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

    stf::smv::IView *put(stf::smv::IView *sender)
    {
        if(mCursor.selectedCell.cell == cells::emptyCell() && mBoard[mCursor.selectableCell.pos]->color() == player)
        {
            mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
        }
        else
        {
            TurnType turn;
            CastlingKing *king = dynamic_cast<CastlingKing*>(mCursor.selectedCell.cell);

            BoardCell *selectedBackUp = mBoard[mCursor.selectedCell.pos];
            BoardCell *selectableBackUp = mBoard[mCursor.selectableCell.pos];

            if(mCursor.selectedCell.cell->view() == King().view()) {
                turn = findCastlingTurn(king);
            }
            if(mCursor.selectedCell.cell->canAttack(mBoard, mCursor.selectedCell.pos, mCursor.selectableCell.pos)) {
                pieceMoveProc();
                turn = TurnType::Attack;
            }
            if(mCursor.selectedCell.cell->canJump(mBoard, mCursor.selectedCell.pos, mCursor.selectableCell.pos)) {
                pieceMoveProc();
                turn = TurnType::Move;
            }

            mBoard.transformPawns();

            TurnType bIsCheckW = mBoard.blackCheckToWhite();
            TurnType wIsCheckB = mBoard.whiteCheckToBlack();

            if(bIsCheckW != TurnType::Nothing)
                turn = bIsCheckW;
            if(wIsCheckB != TurnType::Nothing)
                turn = wIsCheckB;

            if((player == stf::ColorTable::White && turn == TurnType::BCheckToW) || (player == stf::ColorTable::Red && turn == TurnType::WCheckToB))
            {
                stf::Renderer::log<<stf::endl<<"Huinya!!";
                mBoard.place(mCursor.selectedCell.pos, selectedBackUp);
                mBoard.place(mCursor.selectableCell.pos, selectableBackUp);
            }

            if(mBoard.isCheckmate(mCursor.selectableCell.pos, player))
                stf::Renderer::log << stf::endl << "CHECKMATE";

            log.push_back({ mCursor.selectedCell.cell, mCursor.selectedCell.pos, mCursor.selectableCell.pos, turn });

            if(!log.empty())
            stf::Renderer::log << stf::endl <<
                                  log.back().cell->uniqueView() << " from " <<
                                  log.back().from << " to " <<
                                  log.back().to << " " <<
                                  static_cast<uint8_t>(log.back().type);
            mCursor.reset();
            if(turn != TurnType::Nothing)
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
