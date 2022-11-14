#include "bishops.hpp"

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
