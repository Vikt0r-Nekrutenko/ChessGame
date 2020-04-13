#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(const unsigned char color);
    bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) override;
};

#endif // QUEEN_H
