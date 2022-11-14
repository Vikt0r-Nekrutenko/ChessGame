#include "rooks.hpp"

uint8_t Rook::view() const
{
    return 'R';
}

bool Rook::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    return (source.x != destination.x && source.y == destination.y) ||
           (source.x == destination.x && source.y != destination.y);
}
