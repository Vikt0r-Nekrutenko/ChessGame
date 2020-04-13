#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(const unsigned char color);
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};

#endif // ROOK_H
