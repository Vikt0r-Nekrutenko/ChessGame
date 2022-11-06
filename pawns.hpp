#ifndef PAWNS_HPP
#define PAWNS_HPP

#include "pieces.hpp"

class WPawn : public Pawn, public WhiteColoredCell
{
public:
    int uniqueView() const override;
    bool canJump(const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
};

class BPawn : public Pawn, public BlackColoredCell
{
public:
    int uniqueView() const override;
    bool canJump(const stf::Vec2d& selected, const stf::Vec2d& selectable) const override;
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


namespace pieces {
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
static CellCreator<WQueen> wQueen = CellCreator<WQueen>();
static CellCreator<BQueen> bQueen = CellCreator<BQueen>();
}

#endif // PAWNS_HPP
