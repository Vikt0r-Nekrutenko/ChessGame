#include "kings.hpp"
#include "rooks.hpp"
#include "gameboard.hpp"

uint8_t King::view() const
{
    return 'K';
}

bool King::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    float d = source.diff(destination);
    return d >= 1 && d < 1.5;
}

bool King::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return BoardCell::canJump(board, selected, selectable);
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
    if(log.back().type == TurnType::BCheckToW)
        return false;
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, longCastlingPos(), LONGCASTLING_ROOKX, LONGCASTLING_ROOK_OFFSET);
}

bool WKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(log.back().type == TurnType::BCheckToW)
        return false;
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, shortCastlingPos(), SHORTCASTLING_ROOKX, SHORTCASTLING_ROOK_OFFSET);
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
    if(log.back().type == TurnType::WCheckToB)
        return false;
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, longCastlingPos(), LONGCASTLING_ROOKX, LONGCASTLING_ROOK_OFFSET);
}

bool BKing::isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const
{
    if(log.back().type == TurnType::WCheckToB)
        return false;
    return CastlingPiece::isCastlingPossible((BoardCell*)this, board, log, shortCastlingPos(), SHORTCASTLING_ROOKX, SHORTCASTLING_ROOK_OFFSET);
}
