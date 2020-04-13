#include "King.h"
#include <cmath>

King::King(const unsigned char color) : Piece()
{
    m_color = color;
    m_type = 'K';
}

bool King::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    float d = sqrt(pow(cx - dx, 2) + pow(cy - dy, 2));
    if (d < 1 || d > 1.5) return false;
    return true;
}
