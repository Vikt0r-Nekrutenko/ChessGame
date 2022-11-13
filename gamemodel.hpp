#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "gameboard.hpp"
#include "imodel.hpp"

struct Selector
{
    stf::Vec2d pos = stf::Vec2d( 0, 0 );
    BoardCell *cell = cells::emptyCell();
};

struct Cursor
{
    Selector selectableCell;
    Selector selectedCell;

    void reset()
    {
        selectedCell.cell = selectableCell.cell = cells::emptyCell();
    }

    void select(BoardCell *cell)
    {
        selectedCell.pos = selectableCell.pos;
        selectedCell.cell = selectableCell.cell = cell;
    }

    bool isValidForSelect(const BoardCell *cell, const stf::ColorTable player) const
    {
        if(cell->color() != player)
            return false;
        return true;
    }

    bool isValidForPut() const
    {
        if(selectedCell.cell->uniqueView() == cells::emptyCell()->uniqueView())
            return false;
        if(selectableCell.pos.x == selectedCell.pos.x && selectableCell.pos.y == selectedCell.pos.y)
            return false;
        return true;
    }
};

class CastlingKing;

class GameModel : public stf::smv::BaseModel
{
public:

    GameBoard mBoard = GameBoard();
    Cursor mCursor = Cursor();
    std::vector<Note> log;
    stf::ColorTable player = stf::ColorTable::White;

    GameModel();

    TurnType findCastlingTurn();
    TurnType unavailiableTurnHandler(const GameBoard &backup, const stf::ColorTable col, const TurnType isCheckType);

    stf::smv::IView *put(stf::smv::IView *sender);

    stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) override;

};

#endif // GAMEMODEL_HPP
