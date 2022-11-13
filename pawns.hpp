#ifndef PAWNS_HPP
#define PAWNS_HPP

#include "cells.hpp"

class Pawn : virtual public BoardCell
{
public:
    virtual bool isLeftAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) = 0;
    virtual bool isAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) = 0;
    uint8_t view() const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

class WPawn : public Pawn, public WhiteColoredCell
{
public:
    bool isLeftAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) final;
    bool isAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) final;
    int uniqueView() const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

class BPawn : public Pawn, public BlackColoredCell
{
public:
    bool isLeftAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) final;
    bool isAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d& selected, const stf::Vec2d& selectable) final;
    int uniqueView() const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

namespace pieces {
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
}

#endif // PAWNS_HPP
