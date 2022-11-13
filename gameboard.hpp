#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "cells.hpp"

struct Cursor;

class GameBoard
{
public:

    const stf::Vec2d Size { 8, 8 };

    GameBoard();
    GameBoard(const GameBoard& board);

    GameBoard& operator =(const GameBoard& board);
    BoardCell* operator[](const stf::Vec2d& pos) const;
    GameBoard& copyBoard(const GameBoard& board);

    void place(const stf::Vec2d& pos, BoardCell *cell);
    void clear(const stf::Vec2d& pos);
    void transformPawns();
    TurnType makeAttack(const Cursor &cursor);
    TurnType makeMove(const Cursor &cursor);
    TurnType makeTurn(const Cursor &cursor);

    TurnType blackCheckToWhite() const;
    TurnType whiteCheckToBlack() const;
    TurnType isCheck(BoardCell *attackedKing, const stf::ColorTable &playerColor) const;

    stf::Vec2d findKingPos(const BoardCell *king) const;
    bool isCheckmate(const stf::ColorTable &player) const;
    bool possibleMovesExitst();
    bool isMoveToMakeUncheckExist(const stf::Vec2d &selected, const stf::Vec2d &selectable) const;

    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
