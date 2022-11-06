#include "cells.hpp"

stf::sdb::DynamicFieldsAllocator CellAllocator::cellAllocator = stf::sdb::DynamicFieldsAllocator();

uint8_t ViewedCell::view() const
{
    return 0;
}

void *ViewedCell::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}

stf::ColorTable ColoredCell::color() const
{
    return stf::ColorTable::Default;
}

void *ColoredCell::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}

stf::ColorTable WhiteColoredCell::color() const
{
    return stf::ColorTable::White;
}

stf::ColorTable BlackColoredCell::color() const
{
    return stf::ColorTable::Black;
}

int UniqueIntViewedCell::uniqueView() const
{
    return 0;
}

void *UniqueIntViewedCell::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}

void *BoardCell::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
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
