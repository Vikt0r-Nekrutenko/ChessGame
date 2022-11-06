#ifndef CELLS_HPP
#define CELLS_HPP

#include "model.hpp"
#include "renderer.hpp"

class CellAllocator
{
public:
    static stf::sdb::DynamicFieldsAllocator cellAllocator;
};

template<class T>
class CellCreator
{
public:
    T* operator ()()
    {
        return cell = cell == nullptr ? new T() : cell;
    }

    T *cell = nullptr;
};

class ViewedCell
{
public:
    virtual uint8_t view() const;

    void *operator new(size_t size);
};

class ColoredCell
{
public:
    virtual stf::ColorTable color() const;

    void *operator new(size_t size);
};

class WhiteColoredCell : virtual public ColoredCell
{
public:
    stf::ColorTable color() const override;
};

class BlackColoredCell : public ColoredCell
{
public:
    stf::ColorTable color() const override;
};

class UniqueIntViewedCell
{
public:
    virtual int uniqueView() const;

    void *operator new(size_t size);
};

class BoardCell : public ColoredCell, public ViewedCell, public UniqueIntViewedCell
{
public:
    void *operator new(size_t size);
};

class EmptyCell : public BoardCell
{
public:
    uint8_t view() const override;

    stf::ColorTable color() const override;

    int uniqueView() const override;
};

namespace cells
{
static CellCreator<EmptyCell> emptyCell = CellCreator<EmptyCell>();
}

#endif // CELLS_HPP
