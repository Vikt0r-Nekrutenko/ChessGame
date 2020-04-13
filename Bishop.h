#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(const unsigned char color);
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};

#endif // BISHOP_H
