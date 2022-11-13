#include "gamemodel.hpp"
#include "pawns.hpp"

GameModel::GameModel()
{
    log.push_back({cells::emptyCell(), stf::ColorTable::Default, {0,0}, stf::ColorTable::Default, {0,0}, TurnType::Nothing});
}

void GameModel::pieceMoveProc()
{
    mBoard.place(mCursor.selectableCell.pos, mCursor.selectedCell.cell);
    mBoard.clear(mCursor.selectedCell.pos);
}

void GameModel::castlingProc(CastlingKing *king, const stf::Vec2d &kingDPos, const int rookSX, const int rookDX)
{
    mBoard.clear({rookSX, king->y()});
    mBoard.clear(king->uniquePos());

    mBoard.place(kingDPos,                         king->getKing());
    mBoard.place(kingDPos + stf::Vec2d(rookDX, 0), king->getRook());
}

TurnType GameModel::findCastlingTurn()
{
    if(mCursor.selectedCell.cell->view() != King().view())
        return TurnType::Nothing;

    CastlingKing *king = dynamic_cast<CastlingKing*>(mCursor.selectedCell.cell);

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

stf::smv::IView *GameModel::update(stf::smv::IView *sender, const float dt)
{
    if(mBoard.isCheckmate(player) || !mBoard.possibleMovesExitst())
        stf::Renderer::log<<stf::endl<<"Checkmate!";
    return sender;
}

stf::smv::IView *GameModel::put(stf::smv::IView *sender)
{
    if(mCursor.selectedCell.cell == cells::emptyCell() && mBoard[mCursor.selectableCell.pos]->color() == player)
    {
        mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
    }
    else if(mCursor.selectableCell.pos.x != mCursor.selectedCell.pos.x || mCursor.selectableCell.pos.y != mCursor.selectedCell.pos.y)
    {
        TurnType turn = TurnType::Nothing;

        BoardCell *cell = mCursor.selectedCell.cell;
        GameBoard backUp = mBoard;

        stf::Vec2d selected = mCursor.selectedCell.pos;
        stf::Vec2d selectable = mCursor.selectableCell.pos;

        if(log.back().type != TurnType::WCheckToB)
            turn = findCastlingTurn();

        if(cell->canAttack(mBoard, selected, selectable)) {
            pieceMoveProc();
            turn = TurnType::Attack;
        } else if(cell->canJump(mBoard, selected, selectable)) {
            pieceMoveProc();
            turn = TurnType::Move;
        }

        mBoard.transformPawns();

        TurnType bIsCheckW = mBoard.blackCheckToWhite();
        if(bIsCheckW == TurnType::BCheckToW) {
            stf::Renderer::log << stf::endl << "Black check to the white!";
            turn = bIsCheckW;
        }

        if(bIsCheckW == TurnType::BCheckToW && player == stf::ColorTable::White) {
            stf::Renderer::log<<stf::endl<<"UNRESOLVED WHITE KING UNDER ATTACK!";
            mBoard = backUp;
            return sender;
        }

        TurnType wIsCheckB = mBoard.whiteCheckToBlack();
        if(wIsCheckB == TurnType::WCheckToB) {
            stf::Renderer::log << stf::endl << "White check to the black!";
            turn = wIsCheckB;
        }

        if(wIsCheckB == TurnType::WCheckToB && player == stf::ColorTable::Red) {
            stf::Renderer::log<<stf::endl<<"UNRESOLVED BLACK KING UNDER ATTACK!";
            mBoard = backUp;
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

stf::smv::IView *GameModel::keyEventsHandler(stf::smv::IView *sender, const int key)
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

    case 'f':
        player = player == stf::ColorTable::White ? stf::ColorTable::Red : stf::ColorTable::White;
        break;

    case ' ':
        return put(sender);
    }
    return sender;
}
