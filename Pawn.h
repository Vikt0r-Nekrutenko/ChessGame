#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(const unsigned char color);
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};
#endif // PAWN_H
