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

namespace pieces {
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
}

#endif // PAWNS_HPP
