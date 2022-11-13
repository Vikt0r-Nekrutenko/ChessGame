#include "pieces.hpp"
#include "gameboard.hpp"

uint8_t Pawn::view() const
{
    return 'P';
}

bool Pawn::canAttack(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return board[{selectable}]->getOpponent() == board[{selected}]->color() && noPiecesOnWay(board, selected, selectable);
}

bool Pawn::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return board[selectable]->color() == cells::emptyCell()->color() && noPiecesOnWay(board, selected, selectable);
}
