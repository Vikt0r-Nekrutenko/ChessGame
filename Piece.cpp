#include "Piece.h"

void Piece::move()
{
    m_moves++;
}

unsigned Piece::moves() const
{
    return m_moves;
}

unsigned char Piece::color() const
{
    return m_color;
}

unsigned char Piece::type() const
{
    return m_type;
}

bool Piece::canJump() const
{
    return false;
}
