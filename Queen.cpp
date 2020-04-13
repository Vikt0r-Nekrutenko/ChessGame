#include "Queen.h"
#include <cmath>

Queen::Queen(const unsigned char color) : Piece()
{
    m_color = color;
    m_type = 'Q';
}

bool Queen::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    int x = abs(cx - dx);
    int y = abs(cy - dy);

    if (x == y) return true;
    if (cx != dx && cy == dy) return true;
    if (cx == dx && cy != dy) return true;

    return false;
}
