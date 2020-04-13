#include "Knight.h"
#include <cmath>

Knight::Knight(const unsigned char color) : Piece()
{
    m_color = color;
    m_type = 'N';
}

bool Knight::canJump() const
{
    return true;
}

bool Knight::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    float d = sqrt(pow(cx - dx, 2) + pow(cy - dy, 2));
    if (d < 2.2f || d > 2.3f) return false;
    return true;
}
