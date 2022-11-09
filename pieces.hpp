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
    int x() const { return 4; }
    virtual int longCastlingX() const {return 2;}
    virtual int shortCastlingX() const {return 6;}
    virtual int castlingY() const { return -1; }

    stf::Vec2d longCastlingPos() const {return {longCastlingX(), castlingY()};}
    stf::Vec2d shortCastlingPos() const {return {shortCastlingX(), castlingY()};}
    virtual stf::Vec2d uniquePos() const { return { -1, -1 }; }

    bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;
    bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;

    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const final;
};

#endif // PIECES_HPP
