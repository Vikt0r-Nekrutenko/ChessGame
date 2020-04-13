#include "Bishop.h"
#include <cmath>

Bishop::Bishop(const unsigned char color) : Piece()
{
    m_color = color;
    m_type = 'B';
}

bool Bishop::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    int x = abs(cx - dx);
    int y = abs(cy - dy);
    if (x == y) return true;
    return false;
}
