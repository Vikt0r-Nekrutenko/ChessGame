#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "cells.hpp"

struct Cursor;
class CastlingKing;

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
    void makeCastlingTurn(CastlingKing *king, const stf::Vec2d& kingDPos, const int rookSX, const int rookDX);
    TurnType makeAttack(const Cursor &cursor);
    TurnType makeMove(const Cursor &cursor);
    TurnType makeTurn(const Cursor &cursor);
    TurnType shortCastling(const Cursor &cursor, CastlingKing *king, const std::vector<Note> &log);
    TurnType longCastling(const Cursor &cursor, CastlingKing *king, const std::vector<Note> &log);

    TurnType blackCheckToWhite() const;
    TurnType whiteCheckToBlack() const;
    TurnType isCheck(BoardCell *attackedKing, const stf::ColorTable &playerColor) const;

    stf::Vec2d findKingPos(const BoardCell *king) const;
    bool isCheckmate(const stf::ColorTable &player) const;
    bool possibleMovesExitst();
    bool isMoveToMakeUncheckExist(const stf::Vec2d &selected, const stf::Vec2d &selectable) const;

    std::vector<BoardCell *> mBoard;
};

namespace pieces {
static std::map<int, std::string> Pieces = {
    {-6, "Black King"},
    {-5, "Black Queen"},
    {-4, "Black Bishop"},
    {-3, "Black Knight"},
    {-2, "Black Rook"},
    {-1, "Black Pawn"},
    { 0, "Empty Cell"},
    {+1, "White Pawn"},
    {+2, "White Rook"},
    {+3, "White Knight"},
    {+4, "White Bishop"},
    {+5, "White Queen"},
    {+6, "White King"},
};
}

#endif // GAMEBOARD_HPP
