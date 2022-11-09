#ifndef PAWNS_HPP
#define PAWNS_HPP

#include "pieces.hpp"

class WPawn : public Pawn, public WhiteColoredCell
{
public:
    int uniqueView() const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

class BPawn : public Pawn, public BlackColoredCell
{
public:
    int uniqueView() const override;
    bool canJump(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
    bool canAttack(const GameBoard &board, const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};



class WQueen : public Queen, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +5; }
};

class BQueen : public Queen, public BlackColoredCell
{
public:
    int uniqueView() const override { return -5; }
};



class WRook : public Rook, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +2; }
};

class BRook : public Rook, public BlackColoredCell
{
public:
    int uniqueView() const override { return -2; }
};



class WKnight : public Knight, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +3; }
};

class BKnight : public Knight, public BlackColoredCell
{
public:
    int uniqueView() const override { return -3; }
};



class WBishop : public Bishop, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +4; }
};

class BBishop : public Bishop, public BlackColoredCell
{
public:
    int uniqueView() const override { return -4; }
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
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
static CellCreator<WQueen> wQueen = CellCreator<WQueen>();
static CellCreator<BQueen> bQueen = CellCreator<BQueen>();
static CellCreator<WRook> wRook = CellCreator<WRook>();
static CellCreator<BRook> bRook = CellCreator<BRook>();
static CellCreator<WKnight> wKnight = CellCreator<WKnight>();
static CellCreator<BKnight> bKnight = CellCreator<BKnight>();
static CellCreator<WBishop> wBishop = CellCreator<WBishop>();
static CellCreator<BBishop> bBishop = CellCreator<BBishop>();
static CellCreator<WKing> wKing = CellCreator<WKing>();
static CellCreator<BKing> bKing = CellCreator<BKing>();
}

#endif // PAWNS_HPP
