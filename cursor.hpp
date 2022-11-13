#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "cells.hpp"

struct Selector
{
    stf::Vec2d pos = stf::Vec2d( 0, 0 );
    BoardCell *cell = cells::emptyCell();
};

struct Cursor
{
    Selector selectableCell;
    Selector selectedCell;

    void reset();

    void select(BoardCell *cell);

    bool isValidForSelect(const BoardCell *cell, const stf::ColorTable player) const;

    bool isValidForPut() const;
};

#endif // CURSOR_HPP
