#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "pawns.hpp"

class GameBoard
{
public:

    const stf::Vec2d Size { 8, 8 };

    GameBoard()
    {
        for(int i = 0; i < Size.x * Size.y; ++i) {
            mBoard.push_back(cells::emptyCell());
        }

        for(int i = 0; i < Size.x; ++i) {
            mBoard.at(Size.x * 1 + i) = pieces::bPawn();
            mBoard.at(Size.x * 6 + i) = pieces::wPawn();
        }

        mBoard.at(Size.x * 0 + 0) = pieces::bRook();
        mBoard.at(Size.x * 0 + 7) = pieces::bRook();
        mBoard.at(Size.x * 7 + 0) = pieces::wRook();
        mBoard.at(Size.x * 7 + 7) = pieces::wRook();

        mBoard.at(Size.x * 0 + 1) = pieces::bKnight();
        mBoard.at(Size.x * 0 + 6) = pieces::bKnight();
        mBoard.at(Size.x * 7 + 1) = pieces::wKnight();
        mBoard.at(Size.x * 7 + 6) = pieces::wKnight();

        mBoard.at(Size.x * 0 + 2) = pieces::bBishop();
        mBoard.at(Size.x * 0 + 5) = pieces::bBishop();
        mBoard.at(Size.x * 7 + 2) = pieces::wBishop();
        mBoard.at(Size.x * 7 + 5) = pieces::wBishop();

        mBoard.at(Size.x * 0 + 3) = pieces::bQueen();
        mBoard.at(Size.x * 7 + 3) = pieces::wQueen();

        mBoard.at(Size.x * 0 + 4) = pieces::bKing();
        mBoard.at(Size.x * 7 + 4) = pieces::wKing();
    }

    BoardCell* operator[](const stf::Vec2d& pos) const
    {
        return mBoard.at(Size.x * pos.y + pos.x);
    }

    void place(const stf::Vec2d& pos, BoardCell *cell)
    {
        mBoard.at(Size.x * pos.y + pos.x) = cell;
    }

    void clear(const stf::Vec2d& pos)
    {
        mBoard.at(Size.x * pos.y + pos.x) = cells::emptyCell();
    }

    void transformPawns();

    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
