#include "cells.hpp"
#include "gameboard.hpp"

stf::sdb::DynamicFieldsAllocator CellAllocator::cellAllocator = stf::sdb::DynamicFieldsAllocator();

void *BoardCell::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}

uint8_t BoardCell::view() const
{
    return 0;
}

stf::ColorTable BoardCell::color() const
{
    return stf::ColorTable::Default;
}

stf::ColorTable BoardCell::getOpponent() const
{
    return stf::ColorTable::Default;
}

bool BoardCell::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return board[selectable]->color() == cells::emptyCell()->color();
}

bool BoardCell::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return false;
}

bool BoardCell::noPiecesOnWay(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d sub = selectable - selected;
    const stf::Vec2d abss = {std::abs(sub.x), std::abs(sub.y)};

    stf::Vec2d dir = { (sub.x == 0 ? 0 : abss.x / sub.x),
                       (sub.y == 0 ? 0 : abss.y / sub.y) };
    const int lim = std::max(sub.x, sub.y) - 1;

    for(int i = 0; i < lim; ++i) {
        if(board[{ selected + dir }]->color() != cells::emptyCell()->color()) {
            return false;
        }
    }
    return true;
}

int BoardCell::uniqueView() const
{
    return 0;
}

stf::ColorTable WhiteColoredCell::color() const
{
    return stf::ColorTable::White;
}

stf::ColorTable WhiteColoredCell::getOpponent() const
{
    return stf::ColorTable::Red;
}

stf::ColorTable BlackColoredCell::color() const
{
    return stf::ColorTable::Red;
}

stf::ColorTable BlackColoredCell::getOpponent() const
{
    return stf::ColorTable::White;
}

uint8_t EmptyCell::view() const
{
    return ' ';
}

stf::ColorTable EmptyCell::color() const
{
    return stf::ColorTable::Default;
}

int EmptyCell::uniqueView() const
{
    return 0;
}
