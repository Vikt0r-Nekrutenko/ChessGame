#ifndef PIECES_HPP
#define PIECES_HPP

#include "cells.hpp"

class Pawn : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

class Queen : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class Rook : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class Knight : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
    bool noPiecesOnWay(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const final;
};

class Bishop : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

class King : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
};

#endif // PIECES_HPP
