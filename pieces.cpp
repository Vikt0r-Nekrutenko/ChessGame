#include "pieces.hpp"


uint8_t Pawn::view() const
{
    return 'P';
}

bool Pawn::canJump(const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(std::abs((selectable - selected).y) == 1)
        return true;
    return false;
}
