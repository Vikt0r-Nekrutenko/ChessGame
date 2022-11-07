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

uint8_t Queen::view() const
{
    return 'Q';
}

bool Queen::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    const stf::Vec2d pos = destination - source;
    const stf::Vec2d posAbs = { std::abs(pos.x), std::abs(pos.y) };

    const bool diagonals = posAbs.x == posAbs.y;
    const bool vertical  = source.x != destination.x && source.y == destination.y;
    const bool horizontal= source.x == destination.x && source.y != destination.y;

    if (diagonals || vertical || horizontal) {
        return true;
    } return false;
}

uint8_t Rook::view() const
{
    return 'R';
}

bool Rook::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    if (source.x != destination.x && source.y == destination.y) return true;
    if (source.x == destination.x && source.y != destination.y) return true;
    return false;
}
