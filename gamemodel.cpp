#include "gamemodel.hpp"
#include "kings.hpp"


GameModel::GameModel()
{
    log.push_back({cells::emptyCell(), {0,0}, {0,0}, TurnType::Nothing});
}

TurnType GameModel::unavailiableTurnHandler(const GameBoard &backup, const stf::ColorTable col, const TurnType isCheckType)
{
    if(player == col) {
        mBoard = backup;
        return TurnType::Unavailiable;
    } else return isCheckType;
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
    TurnType turn = TurnType::Nothing;
    GameBoard backup = mBoard;

    turn = findCastlingTurn();
    if(turn == TurnType::Nothing)
        turn = mBoard.makeTurn(mCursor);

    mBoard.transformPawns();

    TurnType bIsCheckW = mBoard.blackCheckToWhite();
    if(bIsCheckW == TurnType::BCheckToW)
        turn = unavailiableTurnHandler(backup, stf::ColorTable::White, bIsCheckW);

    TurnType wIsCheckB = mBoard.whiteCheckToBlack();
    if(wIsCheckB == TurnType::WCheckToB)
        turn = unavailiableTurnHandler(backup, stf::ColorTable::Red, wIsCheckB);

    if(mBoard.isCheckmate(player) || !mBoard.possibleMovesExitst())
        stf::Renderer::log<<stf::endl<<"Checkmate!";

    if(turn != TurnType::Nothing)
        log.push_back({ mCursor.selectedCell.cell, mCursor.selectedCell.pos, mCursor.selectableCell.pos, turn });

    stf::Renderer::log << stf::endl <<
                          pieces::Pieces[log.back().cell->uniqueView()] << " " <<
                          cells::Turns[log.back().type] << " from " <<
                          log.back().from << " to " <<
                          log.back().to;
    mCursor.reset();
    if(turn != TurnType::Nothing && turn != TurnType::Unavailiable)
        player = player == stf::ColorTable::White ? stf::ColorTable::Red : stf::ColorTable::White;

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
        if(mCursor.isValidForSelect(mBoard[mCursor.selectableCell.pos], player))
        {
            mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
        } else if(mCursor.isValidForPut()) {
            return put(sender);
        }
    }
    return sender;
}
