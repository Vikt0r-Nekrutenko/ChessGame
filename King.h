#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
    King(const unsigned char color);
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};

#endif // KING_H
