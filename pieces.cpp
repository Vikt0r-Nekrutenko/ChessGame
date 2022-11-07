#include "pieces.hpp"
#include "gameboard.hpp"

auto isOpponent = [](const GameBoard& board, const stf::Vec2d &p0, const stf::Vec2d &p1) -> bool {
    return board[{p1}]->getOpponent() == board[{p0}]->color();
};

uint8_t Pawn::view() const
{
    return 'P';
}

bool Pawn::canAttack(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return isOpponent(board, selected, selectable) && noPiecesOnWay(board, selected, selectable);
}

bool Pawn::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return BoardCell::canJump(board, selected, selectable) && noPiecesOnWay(board, selected, selectable);
}

uint8_t Queen::view() const
{
    return 'Q';
}

bool Queen::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return isOpponent(board, selected, selectable) && canMoveTo(selected, selectable) && noPiecesOnWay(board, selected, selectable);
}

bool Queen::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!BoardCell::canJump(board,selected,selectable))
        return false;

    if(!noPiecesOnWay(board, selected, selectable))
        return false;

    if(!canMoveTo(selected, selectable))
        return false;

    return true;
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
