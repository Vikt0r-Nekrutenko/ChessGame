#include "gamemodel.hpp"
#include "kings.hpp"

GameModel::GameModel()
{
    log.push_back({cells::emptyCell(), stf::ColorTable::Default, {0,0}, stf::ColorTable::Default, {0,0}, TurnType::Nothing});
}

TurnType GameModel::findCastlingTurn()
{
    if(mCursor.selectedCell.cell->view() != King().view())
        return TurnType::Nothing;

    CastlingKing *king = dynamic_cast<CastlingKing*>(mCursor.selectedCell.cell);

    TurnType longC  = mBoard.longCastling(mCursor, king, log);
    TurnType shortC = mBoard.shortCastling(mCursor, king, log);

    return longC == TurnType::LongCastling
            ? longC
            : shortC;
}

stf::smv::IView *GameModel::put(stf::smv::IView *sender)
{
    if(mCursor.isValidForSelect(mBoard[mCursor.selectableCell.pos], player))
    {
        mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
    }
    else if(mCursor.isValidForPut())
    {
        TurnType turn = TurnType::Nothing;
        GameBoard backUp = mBoard;

        turn = findCastlingTurn();
        turn = mBoard.makeTurn(mCursor);
        mBoard.transformPawns();

        TurnType bIsCheckW = mBoard.blackCheckToWhite();
        if(bIsCheckW == TurnType::BCheckToW) {
            if(player == stf::ColorTable::White) {
                mBoard = backUp;
                turn = TurnType::Unresolved;
            } else {
                turn = bIsCheckW;
            }
        }

        TurnType wIsCheckB = mBoard.whiteCheckToBlack();
        if(wIsCheckB == TurnType::WCheckToB) {
            if(player == stf::ColorTable::Red) {
                mBoard = backUp;
                turn = TurnType::Unresolved;
            } else {
                turn = wIsCheckB;
            }
        }

        if(mBoard.isCheckmate(player) || !mBoard.possibleMovesExitst())
            stf::Renderer::log<<stf::endl<<"Checkmate!";

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
                              cells::Turns[log.back().type];
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
