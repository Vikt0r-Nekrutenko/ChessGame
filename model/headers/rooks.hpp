#ifndef ROOKS_HPP
#define ROOKS_HPP

#include "cells.hpp"

class Rook : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class WRook : public Rook, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +2; }
};

class BRook : public Rook, public BlackColoredCell
{
public:
    int uniqueView() const override { return -2; }
};

namespace pieces {
static CellCreator<WRook> wRook = CellCreator<WRook>();
static CellCreator<BRook> bRook = CellCreator<BRook>();
}

#endif // ROOKS_HPP
