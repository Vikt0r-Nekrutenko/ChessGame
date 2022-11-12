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

    GameBoard(const GameBoard& board)
    {
        copyBoard(board);
    }

    GameBoard& operator =(const GameBoard& board)
    {
        return copyBoard(board);
    }

    GameBoard& copyBoard(const GameBoard& board)
    {
        if(mBoard.size() != size_t(Size.x * Size.y))
            mBoard.resize(Size.x * Size.y);

        for(int i = 0; i < Size.x * Size.y; ++i) {
            mBoard.at(i) = board.mBoard.at(i);
        }
        return *this;
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
        return isCheck(pieces::wKing(), stf::ColorTable::Red) == TurnType::Nothing ?  TurnType::Nothing : TurnType::BCheckToW;
    }

    TurnType whiteCheckToBlack() const
    {
        return isCheck(pieces::bKing(), stf::ColorTable::White) == TurnType::Nothing ?  TurnType::Nothing : TurnType::WCheckToB;
    }

    stf::Vec2d findKingPos(const BoardCell *king) const
    {
        stf::Vec2d kingPos {-1,-1};

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                BoardCell *cell = (*this)[{x,y}];
                if(cell->uniqueView() == king->uniqueView()) {
                    return stf::Vec2d{x,y};
                }
            }
        }
        return kingPos;
    }

    TurnType isCheck(BoardCell *attackedKing, const stf::ColorTable &playerColor) const
    {
        stf::Vec2d king {-1,-1};
        std::vector<stf::Vec2d> pieces;

        for(int y = 0; y < Size.y; ++y) {
            for(int x = 0; x < Size.x; ++x) {
                BoardCell *cell = (*this)[{x,y}];
                if(cell->view() == cells::emptyCell()->view())
                    continue;
                if(cell->color() == playerColor) {
                    pieces.push_back({x,y});
                    continue;
                }
                if(cell->uniqueView() == attackedKing->uniqueView()) {
                    king = stf::Vec2d{x,y};
                }
            }
        }

        for(auto &piecePos : pieces) {
            BoardCell *piece = (*this)[{piecePos}];
            if(king != stf::Vec2d{-1,-1} && piece->canAttack(*this,piecePos,king))
                return TurnType::Attack;
        }
        return TurnType::Nothing;
    }

    bool isCheckmate(const stf::ColorTable &player) const
    {
        for(int cy = 0; cy < Size.y; ++cy) {
            for(int cx = 0; cx < Size.x; ++cx) {
                for(int dy = 0; dy < Size.y; ++dy) {
                    for(int dx = 0; dx < Size.x; ++dx) {
                        if((*this)[{cx,cy}]->color() != player)
                            continue;
                        if(stf::Vec2d{cx,cy} == stf::Vec2d{dx,dy})
                            continue;
                        if(isMoveToMakeUncheckExist({cx,cy}, {dx,dy}))
                            return true;
                    }
                }
            }
        }
        return false;
    }

    bool isMoveToMakeUncheckExist(const stf::Vec2d &selected, const stf::Vec2d &selectable) const
    {
        GameBoard tmpBoard = *this;
        BoardCell *cell = tmpBoard[selected];

        if(cell->canAttack(tmpBoard, selected, selectable) || (cell->canJump(tmpBoard, selected, selectable))) {
            tmpBoard.place(selectable, cell);
            tmpBoard.clear(selected);
        }

        TurnType bIsCheckW = tmpBoard.blackCheckToWhite();
        TurnType wIsCheckB = tmpBoard.whiteCheckToBlack();

        if((bIsCheckW == TurnType::BCheckToW) || (wIsCheckB == TurnType::WCheckToB)) {
            return false;
        }
        return true;
    }

    void transformPawns();

    std::vector<BoardCell *> mBoard;
};

#endif // GAMEBOARD_HPP
