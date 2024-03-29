#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "cells.hpp"
#include "pawns.hpp"
#include "rooks.hpp"
#include "knights.hpp"
#include "bishops.hpp"
#include "kings.hpp"
#include "queens.hpp"

#define BOARD_W 8
#define BOARD_H 8

struct Cursor;
class CastlingKing;

class GameBoard
{
public:

    const stf::Vec2d Size { BOARD_W, BOARD_H };

    GameBoard();
    GameBoard(const GameBoard& board);

    GameBoard& operator =(const GameBoard& board);
    BoardCell* operator[](const stf::Vec2d& pos) const;
    GameBoard& copyBoard(const GameBoard& board);

    void place(const size_t i, BoardCell *cell);
    void place(const stf::Vec2d& pos, BoardCell *cell);
    void clear(const stf::Vec2d& pos);
    void transformPawns();
    void makeCastlingTurn(CastlingKing *king, const stf::Vec2d& kingDPos, const int rookSX, const int rookDX);

    TurnType isAttackInPassingAvailiable(const Cursor &cursor, const std::vector<Note> &log);
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

    std::map<int, BoardCell*> Pieces = {
        {-6, pieces::bKing()},
        {-5, pieces::bQueen()},
        {-4, pieces::bBishop()},
        {-3, pieces::bKnight()},
        {-2, pieces::bRook()},
        {-1, pieces::bPawn()},
        { 0, cells::emptyCell()},
        {+1, pieces::wPawn()},
        {+2, pieces::wRook()},
        {+3, pieces::wKnight()},
        {+4, pieces::wBishop()},
        {+5, pieces::wQueen()},
        {+6, pieces::wKing()},
    };
    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
