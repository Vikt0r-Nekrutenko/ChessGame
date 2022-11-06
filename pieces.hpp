#ifndef PIECES_HPP
#define PIECES_HPP

#include "cells.hpp"

class Pawn : virtual public BoardCell
{
    uint8_t view() const override;
};

#endif // PIECES_HPP
