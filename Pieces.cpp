#include "Pieces.h"
#include <cmath>

void Piece::move()
{
    m_moves++;
}

unsigned char Piece::color() const {
    return m_color;
}

unsigned char Piece::type() const {
    return m_type;
}

bool Piece::canJump() const
{
    return false;
}

King::King(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'K';
}

bool King::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
    float d = sqrt(pow(cx - dx, 2) + pow(cy - dy, 2));
    if (d < 1 || d > 1.5) return false;
    return true;
}

Queen::Queen(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'Q';
}

bool Queen::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
    int x = abs(cx - dx);
    int y = abs(cy - dy);

    if (x == y) return true;
    if (cx != dx && cy == dy) return true;
    if (cx == dx && cy != dy) return true;

    return false;
}

Bishop::Bishop(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'B';
}

bool Bishop::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
    int x = abs(cx - dx);
    int y = abs(cy - dy);
    if (x == y) return true;
    return false;
}

Knight::Knight(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'N';
}

bool Knight::canJump() const
{
    return true;
}

bool Knight::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
    float d = sqrt(pow(cx - dx, 2) + pow(cy - dy, 2));
    if (d < 2.2f || d > 2.3f) return false;
    return true;
}

Rook::Rook(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'R';
}

bool Rook::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
    if (cx != dx && cy == dy) return true;
    if (cx == dx && cy != dy) return true;
    return false;
}

Pawn::Pawn(const unsigned char color) : Piece() {
    m_color = color;
    m_type = 'P';
}

bool Pawn::motionValidator(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) {
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
