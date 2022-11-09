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



class WKing : public King, public WhiteColoredCell
{
public:
    int uniqueView() const override { return +6; }

    stf::Vec2d uniquePos() const final { return { x(), 7 }; }
    int castlingY() const final { return 7; }

    bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;
    bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;
};

class BKing : public King, public BlackColoredCell
{
public:
    int uniqueView() const override { return -6; }

    stf::Vec2d uniquePos() const final { return { x(), 0 }; }
    int castlingY() const final { return 0; }

    bool isLongCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;
    bool isShortCastlingPossible(const GameBoard &board, const std::vector<Note> &log) const;
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
