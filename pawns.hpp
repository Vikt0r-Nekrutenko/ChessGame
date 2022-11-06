#ifndef PAWNS_HPP
#define PAWNS_HPP

#include "pieces.hpp"

class WPawn : public Pawn, public WhiteColoredCell
{
public:
    int uniqueView() const override;
};

class BPawn : public Pawn, public BlackColoredCell
{
public:
    int uniqueView() const override;
};

namespace pieces {
static CellCreator<WPawn> wPawn = CellCreator<WPawn>();
static CellCreator<BPawn> bPawn = CellCreator<BPawn>();
}

#endif // PAWNS_HPP
