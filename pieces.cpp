#include "pieces.hpp"
#include "gameboard.hpp"

uint8_t Pawn::view() const
{
    return 'P';
}

bool Pawn::canAttack(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if(std::abs(pos.x) == 1 && std::abs(pos.y) == 1 && board[{selectable}]->getOpponent() == board[{selected}]->color()) {
        return true;
    }
    return false;
}
