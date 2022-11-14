#ifndef KNIGHTS_HPP
#define KNIGHTS_HPP

#include "cells.hpp"

class Knight : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
    bool noPiecesOnWay(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const final;
};

class WKnight : public Knight, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +3; }
};

class BKnight : public Knight, public BlackColoredCell
{
public:
    int uniqueView() const override { return -3; }
};

namespace pieces {
static CellCreator<WKnight> wKnight = CellCreator<WKnight>();
static CellCreator<BKnight> bKnight = CellCreator<BKnight>();
}

#endif // KNIGHTS_HPP
