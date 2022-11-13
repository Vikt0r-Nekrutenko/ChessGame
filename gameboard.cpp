#include "gameboard.hpp"
#include "gamemodel.hpp"
#include "pawns.hpp"
#include "rooks.hpp"
#include "knights.hpp"
#include "bishops.hpp"
#include "kings.hpp"
#include "queens.hpp"

auto findPawnOnLine = [](std::vector<BoardCell *> &board, int beginLine, int endLine, BoardCell *pawn, BoardCell *toPawn){
    for(int x = beginLine; x < endLine; ++x)
        if(board[x]->view() == pawn->view()) {
            board[x] = toPawn;
        }
};

GameBoard::GameBoard()
{
    for(int i = 0; i < Size.x * Size.y; ++i) {
        mBoard.push_back(cells::emptyCell());
    }

//    for(int i = 0; i < Size.x; ++i) {
//        mBoard.at(Size.x * 1 + i) = pieces::bPawn();
//        mBoard.at(Size.x * 6 + i) = pieces::wPawn();
//    }

    mBoard.at(Size.x * 0 + 0) = pieces::bRook();
    mBoard.at(Size.x * 0 + 7) = pieces::bRook();
    mBoard.at(Size.x * 7 + 0) = pieces::wRook();
    mBoard.at(Size.x * 7 + 7) = pieces::wRook();

//    mBoard.at(Size.x * 0 + 1) = pieces::bKnight();
//    mBoard.at(Size.x * 0 + 6) = pieces::bKnight();
//    mBoard.at(Size.x * 7 + 1) = pieces::wKnight();
//    mBoard.at(Size.x * 7 + 6) = pieces::wKnight();

//    mBoard.at(Size.x * 0 + 2) = pieces::bBishop();
//    mBoard.at(Size.x * 0 + 5) = pieces::bBishop();
//    mBoard.at(Size.x * 7 + 2) = pieces::wBishop();
//    mBoard.at(Size.x * 7 + 5) = pieces::wBishop();

//    mBoard.at(Size.x * 0 + 3) = pieces::bQueen();
//    mBoard.at(Size.x * 7 + 3) = pieces::wQueen();

    mBoard.at(Size.x * 0 + 4) = pieces::bKing();
    mBoard.at(Size.x * 7 + 4) = pieces::wKing();
}

GameBoard::GameBoard(const GameBoard &board)
{
    copyBoard(board);
}

GameBoard &GameBoard::operator =(const GameBoard &board)
{
    return copyBoard(board);
}

GameBoard &GameBoard::copyBoard(const GameBoard &board)
{
    if(mBoard.size() != size_t(Size.x * Size.y))
        mBoard.resize(Size.x * Size.y);

    for(int i = 0; i < Size.x * Size.y; ++i) {
        mBoard.at(i) = board.mBoard.at(i);
    }
    return *this;
}

BoardCell *GameBoard::operator[](const stf::Vec2d &pos) const
{
    if(pos.x < 0 || pos.x >= Size.x || pos.y < 0 || pos.y >= Size.y)
        return cells::emptyCell();
    return mBoard.at(Size.x * pos.y + pos.x);
}

void GameBoard::place(const stf::Vec2d &pos, BoardCell *cell)
{
    if(pos.x >= 0 && pos.x < Size.x && pos.y >= 0 && pos.y < Size.y)
        mBoard.at(Size.x * pos.y + pos.x) = cell;
}

void GameBoard::clear(const stf::Vec2d &pos)
{
    if(pos.x >= 0 && pos.x < Size.x && pos.y >= 0 && pos.y < Size.y)
        mBoard.at(Size.x * pos.y + pos.x) = cells::emptyCell();
}

TurnType GameBoard::makeTurn(const Cursor &cursor)
{
    if((*this)[cursor.selectedCell.pos]->canAttack(*this, cursor.selectedCell.pos, cursor.selectableCell.pos))
        return makeAttack(cursor);
    else if((*this)[cursor.selectedCell.pos]->canJump(*this, cursor.selectedCell.pos, cursor.selectableCell.pos))
        return makeMove(cursor);
    return TurnType::Nothing;
}

TurnType GameBoard::makeAttack(const Cursor &cursor)
{
    place(cursor.selectableCell.pos, cursor.selectedCell.cell);
    clear(cursor.selectedCell.pos);
    return TurnType::Attack;
}

TurnType GameBoard::makeMove(const Cursor &cursor)
{
    place(cursor.selectableCell.pos, cursor.selectedCell.cell);
    clear(cursor.selectedCell.pos);
    return TurnType::Move;
}

TurnType GameBoard::blackCheckToWhite() const
{
    return isCheck(pieces::wKing(), stf::ColorTable::Red) == TurnType::Nothing ?  TurnType::Nothing : TurnType::BCheckToW;
}

TurnType GameBoard::whiteCheckToBlack() const
{
    return isCheck(pieces::bKing(), stf::ColorTable::White) == TurnType::Nothing ?  TurnType::Nothing : TurnType::WCheckToB;
}

stf::Vec2d GameBoard::findKingPos(const BoardCell *king) const
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

TurnType GameBoard::isCheck(BoardCell *attackedKing, const stf::ColorTable &playerColor) const
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

bool GameBoard::isCheckmate(const stf::ColorTable &player) const
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
                        return false;
                }
            }
        }
    }
    return true;
}

bool GameBoard::possibleMovesExitst()
{
    GameBoard tmpBoard = *this;
    stf::Vec2d king = findKingPos(pieces::bKing());
    tmpBoard.clear(king);

    for(int dy = king.y - 1; dy < king.y + 2; ++dy) {
        for(int dx = king.x - 1; dx < king.x + 2; ++dx) {
            if(dx < 0 || dx >= Size.x || dy < 0 || dy >= Size.y)
                continue;
            if(stf::Vec2d{dx,dy} == king)
                continue;

            tmpBoard.place({dx,dy}, pieces::bKing());
            TurnType wIsCheckB = tmpBoard.whiteCheckToBlack();

            if(wIsCheckB == TurnType::Nothing)
                return true;
            tmpBoard.clear({dx,dy});
        }
    }
    return false;
}

bool GameBoard::isMoveToMakeUncheckExist(const stf::Vec2d &selected, const stf::Vec2d &selectable) const
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

void GameBoard::transformPawns()
{
    findPawnOnLine(mBoard, 0, Size.x, pieces::wPawn(), pieces::wQueen());
    findPawnOnLine(mBoard, Size.x * Size.y - Size.x, Size.x * Size.y, pieces::bPawn(), pieces::bQueen());
}
