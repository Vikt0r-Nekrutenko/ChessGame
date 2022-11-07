#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "pawns.hpp"
#include "players.hpp"

class GameBoard
{
public:

    const stf::Vec2d Size { 8, 8 };

    GameBoard()
    {
        for(int i = 0; i < Size.x * Size.y; ++i) {
            mBoard.push_back(cells::emptyCell());
        }

//        for(int i = 0; i < Size.x; ++i) {
//            mBoard.at(Size.x * 1 + i) = pieces::bPawn();
//            mBoard.at(Size.x * 6 + i) = pieces::wPawn();
//        }

//        mBoard.at(Size.x * 0 + 0) = pieces::bRook();
//        mBoard.at(Size.x * 0 + 7) = pieces::bRook();
//        mBoard.at(Size.x * 7 + 0) = pieces::wRook();
//        mBoard.at(Size.x * 7 + 7) = pieces::wRook();

//        mBoard.at(Size.x * 0 + 1) = pieces::bKnight();
//        mBoard.at(Size.x * 0 + 6) = pieces::bKnight();
//        mBoard.at(Size.x * 7 + 1) = pieces::wKnight();
//        mBoard.at(Size.x * 7 + 6) = pieces::wKnight();

//        mBoard.at(Size.x * 0 + 2) = pieces::bBishop();
//        mBoard.at(Size.x * 0 + 5) = pieces::bBishop();
//        mBoard.at(Size.x * 7 + 2) = pieces::wBishop();
//        mBoard.at(Size.x * 7 + 5) = pieces::wBishop();

//        mBoard.at(Size.x * 0 + 3) = pieces::bQueen();
//        mBoard.at(Size.x * 7 + 3) = pieces::wQueen();

        mBoard.at(Size.x * 0 + 4) = pieces::bKing();
        mBoard.at(Size.x * 3 + 4) = pieces::wKing();
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

    bool isCheck(const stf::ColorTable &playerColor, const stf::Vec2d &selectable) const
    {
        stf::Vec2d king {0,0};
        std::vector<stf::Vec2d> pieces;

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                if((*this)[{x,y}]->view() == cells::emptyCell()->view())
                    continue;
                if((*this)[{x,y}]->color() == playerColor)
                    continue;

                pieces.push_back({x,y});

                if((*this)[{x,y}]->view() != King().view())
                    continue;

                king = stf::Vec2d{x,y};
            }
        }

        for(auto pos : pieces) {
            if((*this)[pos]->canAttack(*this, pos, king)) {
                stf::Renderer::log<<"CHECK!!!";
                return true;
            }
        }

        return false;
    }

    bool isCheckmate(const stf::Vec2d &selectable, const stf::ColorTable &playerColor) const
    {
        return (*this)[selectable]->color() != playerColor && (*this)[selectable]->view() == King().view();
    }

    void transformPawns();

    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
