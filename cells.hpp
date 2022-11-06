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

class GameBoard;

class BoardCell
{
public:
    void *operator new(size_t size);
    virtual int uniqueView() const;
    virtual uint8_t view() const;
    virtual stf::ColorTable color() const;
    virtual stf::ColorTable getOpponent() const;

    virtual bool canJump(const stf::Vec2d& selected, const stf::Vec2d& selectable) const;
    virtual bool canAttack(const GameBoard& board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const;
};

class WhiteColoredCell : virtual public BoardCell
{
public:
    stf::ColorTable color() const final;
    stf::ColorTable getOpponent() const final;
};

class BlackColoredCell : virtual public BoardCell
{
public:
    stf::ColorTable color() const final;
    stf::ColorTable getOpponent() const final;
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
