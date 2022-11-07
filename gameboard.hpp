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

        mBoard.at(11) = pieces::bPawn();
        mBoard.at(50) = pieces::wQueen();
        mBoard.at(58) = pieces::wKnight();
        mBoard.at(20) = pieces::bRook();
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
