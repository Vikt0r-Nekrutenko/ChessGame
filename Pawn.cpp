#include "Pawn.h"

Pawn::Pawn(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'P';
}

bool Pawn::motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent)
{
    if (opponent == nullptr) {
        if (m_color == 'B') {
            if (dx == cx && dy - cy == -1) {
                return true;
            } else if (dx == cx && dy - cy == -2 && m_moves == 0) {
                return true;
            }
        } else if (m_color == 'W') {
            if (dx == cx && dy - cy == +1) {
                return true;
            } else if (dx == cx && dy - cy == +2 && m_moves == 0) {
                return true;
            }
        }
    } else {
        if (m_color == 'B') {
            if ((dx - cx == -1 && dy - cy == -1) || (dx - cx == +1 && dy - cy == -1)) {
                return true;
            }
        } else if (m_color == 'W') {
            if ((dx - cx == -1 && dy - cy == +1) || (dx - cx == +1 && dy - cy == +1)) {
                return true;
            }
        }
    }
    return false;
}
