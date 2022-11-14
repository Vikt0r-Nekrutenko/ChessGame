#include "knights.hpp"

uint8_t Knight::view() const
{
    return 'N';
}

bool Knight::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    float d = source.diff(destination);
    return d > 2.2f && d < 2.3f;
}

bool Knight::noPiecesOnWay(const GameBoard &, const stf::Vec2d &, const stf::Vec2d &) const
{
    return true;
}
