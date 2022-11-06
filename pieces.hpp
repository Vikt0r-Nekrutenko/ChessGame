#ifndef PIECES_HPP
#define PIECES_HPP

#include "cells.hpp"

class Pawn : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const final;
};

class Queen : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const final;
};

#endif // PIECES_HPP
