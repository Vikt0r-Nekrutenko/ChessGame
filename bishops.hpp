#ifndef BISHOPS_HPP
#define BISHOPS_HPP

#include "cells.hpp"

class Bishop : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class WBishop : public Bishop, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +4; }
};

class BBishop : public Bishop, public BlackColoredCell
{
public:
    int uniqueView() const override { return -4; }
};

namespace pieces {
static CellCreator<WBishop> wBishop = CellCreator<WBishop>();
static CellCreator<BBishop> bBishop = CellCreator<BBishop>();
}

#endif // BISHOPS_HPP
