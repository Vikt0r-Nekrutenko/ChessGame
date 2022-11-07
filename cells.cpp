#include "cells.hpp"
#include "gameboard.hpp"

stf::sdb::DynamicFieldsAllocator CellAllocator::cellAllocator = stf::sdb::DynamicFieldsAllocator();

auto isOpponent = [](const GameBoard& board, const stf::Vec2d &p0, const stf::Vec2d &p1) -> bool {
    return board[{p1}]->getOpponent() == board[{p0}]->color();
};

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
    return canMoveTo(selected, selectable) && noPiecesOnWay(board, selected, selectable) && board[{selectable}]->view() == cells::emptyCell()->view();
}

bool BoardCell::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!isOpponent(board, selected, selectable))
        return false;
    if(!canMoveTo(selected,selectable))
        return false;
    if(!noPiecesOnWay(board,selected,selectable))
        return false;
    return true;
}

bool BoardCell::noPiecesOnWay(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d sub = selectable - selected;
    const stf::Vec2d abss = {std::abs(sub.x), std::abs(sub.y)};

    stf::Vec2d dir = { (sub.x == 0 ? 0 : sub.x / abss.x),
                       (sub.y == 0 ? 0 : sub.y / abss.y) };
    const int lim = std::max(abss.x, abss.y) - 1;
    auto pos = selected;

    for(int i = 0; i < lim; ++i) {
        if(board[{ pos += dir }]->color() != cells::emptyCell()->color()) {
            return false;
        }
    }
    return true;
}

bool BoardCell::canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const
{
    return false;
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
