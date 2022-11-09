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

bool CastlingPiece::isCastlingPossible(BoardCell *cell, const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d &castlingPos, const int rookX, const int rookXDest) const
{
    if(!cell->noMovesYet(log, uniquePos()))
        return false;

    if(board[{rookX,y()}]->view() != Rook().view())
        return false;

    if(!board[{rookX,y()}]->noMovesYet(log, {rookX, y()}))
        return false;

    if(!cell->noPiecesOnWay(board, uniquePos(), castlingPos))
        return false;

    if(!cell->noPiecesOnWay(board, {rookX, y()}, castlingPos + stf::Vec2d(rookXDest,0)))
        return false;

    return true;
}

BoardCell *WKing::getKing() const
{
    return pieces::wKing();
}

BoardCell *WKing::getRook() const
{
    return pieces::wRook();
}

bool WKing::isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, longCastlingPos(), 0, +1);
}

bool WKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, shortCastlingPos(), 7, -1);
}

BoardCell *BKing::getKing() const
{
    return pieces::bKing();
}

BoardCell *BKing::getRook() const
{
    return pieces::bRook();
}

bool BKing::isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, longCastlingPos(), 0, +1);
}

bool BKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, shortCastlingPos(), 7, -1);
}
