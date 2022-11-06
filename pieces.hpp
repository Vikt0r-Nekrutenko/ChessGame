#ifndef PIECES_HPP
#define PIECES_HPP

#include "cells.hpp"

class Pawn : virtual public BoardCell
{
public:
    uint8_t view() const override;
};

#endif // PIECES_HPP
