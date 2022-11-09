#include "pawns.hpp"
#include "gameboard.hpp"

#define WPAWN_SPAWN_Y 6
#define BPAWN_SPAWN_Y 1

int WPawn::uniqueView() const
{
    return +1;
}

int BPawn::uniqueView() const
{
    return -1;
}

bool WPawn::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!Pawn::canJump(board, selected, selectable))
        return false;
    if(selectable - selected == stf::Vec2d(0, -1))
        return true;
    else if(selected.y == WPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, -2))
        return true;
    return false;
}

bool WPawn::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if((pos == stf::Vec2d(+1, -1) || pos == stf::Vec2d(-1, -1)) && Pawn::canAttack(board, selected, selectable)) {
        return true;
    } return false;
}

bool BPawn::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!Pawn::canJump(board, selected, selectable))
        return false;
    if(selectable - selected == stf::Vec2d(0, +1))
        return true;
    else if(selected.y == BPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, +2))
        return true;
    return false;
}

bool BPawn::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if((pos == stf::Vec2d(+1, +1) || pos == stf::Vec2d(-1, +1)) && Pawn::canAttack(board, selected, selectable)) {
        return true;
    } return false;
}

bool WKing::isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(!noMovesYet(log, uniquePos()))
        return false;

    if(board[{0,castlingY()}]->view() != pieces::wRook()->view())
        return false;

    if(!board[{0,castlingY()}]->noMovesYet(log, {0,castlingY()}))
        return false;

    if(!noPiecesOnWay(board, uniquePos(), longCastlingPos()))
        return false;

    if(!noPiecesOnWay(board, {0,castlingY()}, longCastlingPos() + stf::Vec2d(+1,0)))
        return false;

    return true;
}

bool WKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(!noMovesYet(log, uniquePos()))
        return false;

    if(board[{7,castlingY()}]->view() != pieces::wRook()->view())
        return false;

    if(!board[{7,castlingY()}]->noMovesYet(log, {7,castlingY()}))
        return false;

    if(!noPiecesOnWay(board, uniquePos(), shortCastlingPos()))
        return false;

    if(!noPiecesOnWay(board, {7,castlingY()}, shortCastlingPos() + stf::Vec2d(-1,0)))
        return false;

    return true;
}

bool BKing::isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(!noMovesYet(log, uniquePos()))
        return false;

    if(board[{0,castlingY()}]->view() != pieces::wRook()->view())
        return false;

    if(!board[{0,castlingY()}]->noMovesYet(log, {0,castlingY()}))
        return false;

    if(!noPiecesOnWay(board, uniquePos(), longCastlingPos()))
        return false;

    if(!noPiecesOnWay(board, {0,castlingY()}, longCastlingPos() + stf::Vec2d(+1,0)))
        return false;

    return true;
}

bool BKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(!noMovesYet(log, uniquePos()))
        return false;

    if(board[{7,castlingY()}]->view() != pieces::wRook()->view())
        return false;

    if(!board[{7,castlingY()}]->noMovesYet(log, {7,castlingY()}))
        return false;

    if(!noPiecesOnWay(board, uniquePos(), shortCastlingPos()))
        return false;

    if(!noPiecesOnWay(board, {7,castlingY()}, shortCastlingPos() + stf::Vec2d(-1,0)))
        return false;

    return true;
}
