#include "pieces.hpp"
#include "gameboard.hpp"

auto isOpponent = [](const GameBoard& board, const stf::Vec2d &p0, const stf::Vec2d &p1) -> bool {
    return board[{p1}]->getOpponent() == board[{p0}]->color();
};

auto isSamePlayer = [](const GameBoard &board, const stf::Vec2d &p0, const stf::Vec2d &p1) {
    return board[{p1}]->color() != board[{p0}]->color();
};

uint8_t Pawn::view() const
{
    return 'P';
}

bool Pawn::canAttack(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if(std::abs(pos.x) == 1 && std::abs(pos.y) == 1 && isOpponent(board, selected, selectable)) {
        return true;
    } return false;
}

bool Pawn::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return isSamePlayer(board, selected, selectable);
}

uint8_t Queen::view() const
{
    return 'Q';
}

bool Queen::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return canJump(board, selected, selectable) && isOpponent(board, selected, selectable);
}

bool Queen::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    const stf::Vec2d posAbs = { std::abs(pos.x), std::abs(pos.y) };

    const bool diagonals = posAbs.x == posAbs.y;
    const bool vertical  = selected.x != selectable.x && selected.y == selectable.y;
    const bool horizontal= selected.x == selectable.x && selected.y != selectable.y;

    if (diagonals || vertical || horizontal) {
        return isSamePlayer(board, selected, selectable);
    } return false;
}
