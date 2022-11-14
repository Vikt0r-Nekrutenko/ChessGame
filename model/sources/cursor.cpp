#include "cursor.hpp"


void Cursor::reset()
{
    selectedCell.cell = selectableCell.cell = cells::emptyCell();
}

void Cursor::select(BoardCell *cell)
{
    selectedCell.pos = selectableCell.pos;
    selectedCell.cell = selectableCell.cell = cell;
}

bool Cursor::isValidForSelect(const BoardCell *cell, const stf::ColorTable player) const
{
    if(cell->color() != player)
        return false;
    return true;
}

bool Cursor::isValidForPut() const
{
    if(selectedCell.cell->uniqueView() == cells::emptyCell()->uniqueView())
        return false;
    if(selectableCell.pos.x == selectedCell.pos.x && selectableCell.pos.y == selectedCell.pos.y)
        return false;
    return true;
}
