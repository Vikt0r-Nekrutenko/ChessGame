#ifndef KINGS_HPP
#define KINGS_HPP

#include "cells.hpp"

class King : virtual public BoardCell
{
public:
    uint8_t view() const override;
    bool canMoveTo(const stf::Vec2d &source, const stf::Vec2d &destination) const final;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const final;
};

class CastlingPiece
{
public:
    virtual int x() const = 0;
    virtual int longCastlingX() const = 0;
    virtual int shortCastlingX() const = 0;
    virtual int y() const = 0;

    stf::Vec2d uniquePos() const { return {x(), y()}; }
    stf::Vec2d longCastlingPos() const {return {longCastlingX(), y()};}
    stf::Vec2d shortCastlingPos() const {return {shortCastlingX(), y()};}

    bool isCastlingPossible(BoardCell *cell, const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d &castlingPos, const int rookX, const int rookXDest) const;
    virtual bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const = 0;
    virtual bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const = 0;
};

class CastlingKing : public CastlingPiece
{
public:
    int x() const final { return 4; }
    int longCastlingX() const override {return 2;}
    int shortCastlingX() const override {return 6;}

    virtual BoardCell *getKing() const = 0;
    virtual BoardCell *getRook() const = 0;
};

class WKing : public King, public WhiteColoredCell, public CastlingKing
{
public:
    int y() const final { return 7; }
    int uniqueView() const override { return +6; }

    BoardCell *getKing() const final;
    BoardCell *getRook() const final;

    bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const override;
    bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const override;
};

class BKing : public King, public BlackColoredCell, public CastlingKing
{
public:
    int y() const final { return 0; }
    int uniqueView() const override { return -6; }

    BoardCell *getKing() const final;
    BoardCell *getRook() const final;

    bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const override;
    bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const override;
};

namespace pieces {
static CellCreator<WKing> wKing = CellCreator<WKing>();
static CellCreator<BKing> bKing = CellCreator<BKing>();
}
#endif // KINGS_HPP
