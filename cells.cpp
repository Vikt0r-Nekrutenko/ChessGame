#include "cells.hpp"

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

int BoardCell::uniqueView() const
{
    return 0;
}

stf::ColorTable WhiteColoredCell::color() const
{
    return stf::ColorTable::White;
}

stf::ColorTable BlackColoredCell::color() const
{
    return stf::ColorTable::Red;
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
