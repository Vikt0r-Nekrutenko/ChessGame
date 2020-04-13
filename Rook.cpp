#include "Rook.h"

Rook::Rook(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'R';
}

bool Rook::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    if (cx != dx && cy == dy) return true;
    if (cx == dx && cy != dy) return true;
    return false;
}
