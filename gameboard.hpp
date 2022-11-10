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

        mBoard.at(Size.x * 0 + 0) = pieces::bRook();
        mBoard.at(Size.x * 0 + 7) = pieces::bRook();
        mBoard.at(Size.x * 7 + 0) = pieces::wRook();
        mBoard.at(Size.x * 7 + 7) = pieces::wRook();

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

    TurnType blackCheckToWhite() const
    {
        stf::Vec2d whiteKing {-1,-1};
        std::vector<stf::Vec2d> blackPieces;

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                BoardCell *cell = (*this)[{x,y}];
                if(cell->view() == cells::emptyCell()->view())
                    continue;
                if(cell->color() == stf::ColorTable::Red) {
                    blackPieces.push_back({x,y});
                    continue;
                }
                if(cell->uniqueView() == pieces::wKing()->uniqueView()) {
                    whiteKing = stf::Vec2d{x,y};
                }
            }
        }

        for(auto &piecePos : blackPieces) {
            BoardCell *piece = (*this)[{piecePos}];
            if(piece->canAttack(*this,piecePos,whiteKing))
                return TurnType::BCheckToW;
        }
        return TurnType::Nothing;
    }

    TurnType whiteCheckToBlack() const
    {
        stf::Vec2d blackKing {-1,-1};
        std::vector<stf::Vec2d> whitePieces;

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                BoardCell *cell = (*this)[{x,y}];
                if(cell->view() == cells::emptyCell()->view())
                    continue;
                if(cell->color() == stf::ColorTable::White) {
                    whitePieces.push_back({x,y});
                    continue;
                }
                if(cell->uniqueView() == pieces::bKing()->uniqueView()) {
                    blackKing = stf::Vec2d{x,y};
                }
            }
        }

        for(auto &piecePos : whitePieces) {
            BoardCell *piece = (*this)[{piecePos}];
            if(piece->canAttack(*this,piecePos,blackKing))
                return TurnType::WCheckToB;
        }
        return TurnType::Nothing;
    }



    TurnType isCheck(const stf::ColorTable &playerColor) const
    {
        stf::Vec2d king1 {-1,-1};
        stf::Vec2d king2 {-1,-1};
        std::vector<stf::Vec2d> pieces1;
        std::vector<stf::Vec2d> pieces2;

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                BoardCell *cell = (*this)[{x,y}];

                if(cell->view() == cells::emptyCell()->view())
                    continue;

                if(cell->uniqueView() == pieces::wKing()->uniqueView())
                    king1 = stf::Vec2d({x,y});

                if(cell->uniqueView() == pieces::bKing()->uniqueView())
                    king2 = stf::Vec2d{x,y};

                if(cell->color() != playerColor) {
                    pieces1.push_back({x,y});
                }

                if(cell->color() == playerColor) {
                    pieces2.push_back({x,y});
                }

            }
        }

        for(auto pos : pieces1) {
            if(king1 != stf::Vec2d(-1,-1) && (*this)[pos]->canAttack(*this, pos, king1)) {
                return TurnType::BCheckToW;
            }
        }
        for(auto pos : pieces2) {
            if(king2 != stf::Vec2d(-1,-1) && (*this)[pos]->canAttack(*this, pos, king2)) {
                return TurnType::WCheckToB;
            }
        }

        return TurnType::Nothing;
    }

    bool isCheckmate(const stf::Vec2d &selectable, const stf::ColorTable &playerColor) const
    {
        return (*this)[selectable]->color() != playerColor && (*this)[selectable]->view() == King().view();
    }

    void transformPawns();

    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
