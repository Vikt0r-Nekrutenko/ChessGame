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

    return diagonals || vertical || horizontal;
}

uint8_t Rook::view() const
{
    return 'R';
}

bool Rook::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    return (source.x != destination.x && source.y == destination.y) ||
           (source.x == destination.x && source.y != destination.y);
}




uint8_t Knight::view() const
{
    return 'N';
}

bool Knight::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    float d = source.diff(destination);
    return d > 2.2f && d < 2.3f;
}

bool Knight::noPiecesOnWay(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return true;
}



uint8_t Bishop::view() const
{
    return 'B';
}

bool Bishop::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    int x = abs(source.x - destination.x);
    int y = abs(source.y - destination.y);
    return x == y;
}

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
