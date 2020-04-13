#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(const unsigned char color);
    bool canJump() const override;
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};

#endif // KNIGHT_H
