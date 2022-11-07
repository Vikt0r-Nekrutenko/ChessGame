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

namespace pieces {
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
static CellCreator<WQueen> wQueen = CellCreator<WQueen>();
static CellCreator<BQueen> bQueen = CellCreator<BQueen>();
static CellCreator<WRook> wRook = CellCreator<WRook>();
static CellCreator<BRook> bRook = CellCreator<BRook>();
static CellCreator<WKnight> wKnight = CellCreator<WKnight>();
static CellCreator<BKnight> bKnight = CellCreator<BKnight>();
}

#endif // PAWNS_HPP
