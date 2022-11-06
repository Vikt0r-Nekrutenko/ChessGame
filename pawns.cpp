#include "pawns.hpp"

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

bool WPawn::canJump(const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(selectable - selected == stf::Vec2d(0, -1))
        return true;
    else if(selected.y == WPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, -2))
        return true;
    return false;
}

bool BPawn::canJump(const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(selectable - selected == stf::Vec2d(0, +1))
        return true;
    else if(selected.y == BPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, +2))
        return true;
    return false;
}
