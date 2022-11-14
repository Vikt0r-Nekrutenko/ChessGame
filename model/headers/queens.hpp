#ifndef QUEENS_HPP
#define QUEENS_HPP

#include "cells.hpp"

class Queen : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class WQueen : public Queen, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +5; }
};

class BQueen : public Queen, public BlackColoredCell
{
public:
    int uniqueView() const override { return -5; }
};

namespace pieces {
static CellCreator<WQueen> wQueen = CellCreator<WQueen>();
static CellCreator<BQueen> bQueen = CellCreator<BQueen>();
}

#endif // QUEENS_HPP
