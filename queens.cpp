#include "queens.hpp"

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
