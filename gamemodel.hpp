#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "gameboard.hpp"
#include "imodel.hpp"
#include "cursor.hpp"

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
