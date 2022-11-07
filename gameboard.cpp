#include "gameboard.hpp"

auto findPawnOnLine = [](std::vector<BoardCell *> &board, int beginLine, int endLine, BoardCell *pawn, BoardCell *toPawn){
    for(int x = beginLine; x < endLine; ++x)
        if(board[x]->view() == pawn->view()) {
            board[x] = toPawn;
        }
};

void GameBoard::transformPawns()
{
    findPawnOnLine(mBoard, 0, Size.x, pieces::wPawn(), pieces::wQueen());
    findPawnOnLine(mBoard, Size.x * Size.y - Size.x, Size.x * Size.y, pieces::bPawn(), pieces::bQueen());
}
