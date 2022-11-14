#ifndef CELLS_HPP
#define CELLS_HPP

#include "fieldsallocator.hpp"
#include "renderer.hpp"
#include <list>
#include <iostream>
#include <map>

class BoardCell;

enum class TurnType : uint8_t
{
    Nothing,
    Unavailiable,
    Move,
    Attack,
    AttackInPassing,
    LongCastling,
    ShortCastling,
    WCheckToB,
    BCheckToW,
};

struct Note
{
    BoardCell *cell;
    stf::Vec2d from;
    stf::Vec2d to;
    TurnType type;
};

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

    virtual bool canJump(const GameBoard& board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const;
    virtual bool canAttack(const GameBoard& board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const;
    virtual bool noPiecesOnWay(const GameBoard& board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const;
    virtual bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const;

    virtual bool noMovesYet(const std::vector<Note> &log, const stf::Vec2d &pos) const;
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

static std::map<TurnType, std::string> Turns = {
    {TurnType::Nothing, "Nothing"} ,
    {TurnType::Unavailiable, "NOT"} ,
    {TurnType::Move, "-"} ,
    {TurnType::Attack, "x"} ,
    {TurnType::AttackInPassing, "x"} ,
    {TurnType::LongCastling, "0-0-0"} ,
    {TurnType::ShortCastling, "0-0"} ,
    {TurnType::WCheckToB, "+"} ,
    {TurnType::BCheckToW, "+"} ,
};
}

#endif // CELLS_HPP
