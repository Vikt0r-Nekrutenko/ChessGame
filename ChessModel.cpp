#include "ChessModel.h"
#include "Pieces.h"
#include <iostream>

ChessModel::ChessModel() {
    map.resize(N * N, nullptr);

    for (int x = 0; x < N; x++) {
        map[N + x] = new Pawn('W');
        map[N * 6 + x] = new Pawn('B');
    }

    map[0] = new Rook('W');
    map[N - 1] = new Rook('W');
    map[N * 7] = new Rook('B');
    map[N * 7 + 7] = new Rook('B');

    map[1] = new Knight('W');
    map[N - 2] = new Knight('W');
    map[N * 7 + 1] = new Knight('B');
    map[N * 7 + 6] = new Knight('B');

    map[2] = new Bishop('W');
    map[N - 3] = new Bishop('W');
    map[N * 7 + 2] = new Bishop('B');
    map[N * 7 + 5] = new Bishop('B');

    map[3] = new King('W');
    map[N * 7 + 3] = new King('B');

    map[4] = new Queen('W');
    map[N * 7 + 4] = new Queen('B');

    map[N * 5 + 1] = map[N + 1];
    map[N + 1] = nullptr;
}

ChessModel::~ChessModel()
{
    for (int i = map.size() - 1; i >= 0; i--) {
        delete map[i];
    }
}

Piece *ChessModel::get(const int x, const int y)
{
    return map[N * y + x];
}

Piece *ChessModel::get(const int indx) const
{
    return map[indx];
}

bool ChessModel::coordIsValid(const int cX, const int cY, const int dX, const int dY) const
{
    if ((cX >= 'a' && cX <= 'h' && cY >= '1' && cY <= '8') && (dX >= 'a' && dX <= 'h' && dY >= '1' && dY <= '8')) {
        return true;
    }
    return false;
}

bool ChessModel::pieceIsJumping(int cX, int cY, const int dX, const int dY) const
{
    int X = abs(dX - cX), Y = abs(dY - cY);
    int _X = dX - cX; _X = (_X == 0) ? 0 : _X / X;
    int _Y = dY - cY; _Y = (_Y == 0) ? 0 : _Y / Y;
    int lim = (X > Y ? X : Y) - 1;

    for (int i = 0; i < lim; i++) {
        if (map[N * (cY += _Y) + (cX += _X)] != nullptr) {
            return true;
        }
    }
    return false;
}

void ChessModel::move(const int cX, const int cY, const int dX, const int dY)
{
    if (!coordIsValid(cX, cY, dX, dY)) {
        std::cout << "coordinate is not valid" << std::endl;
        return;
    }

    int cx = cX - 'a';
    int cy = cY - '1';
    int dx = dX - 'a';
    int dy = dY - '1';

    int curIndx = N * cy + cx;
    int destIndx = N * dy + dx;

    // check existing the piece
    if (map[curIndx] == nullptr) {
        std::cout << "piece is not exist" << std::endl;
        return;
    }

    // check player
    if (map[curIndx]->color() != m_player) {
        std::cout << "another player move" << std::endl;
        return;
    }

    // check motion
    if (!map[curIndx]->motionValidator(cx, cy, dx, dy, map[destIndx])) {
        std::cout << "not allowed" << std::endl;
        return;
    }

    // check jumping
    if (!map[curIndx]->canJump() && pieceIsJumping(cx, cy, dx, dy)) {
        std::cout << "jumps not allowed" << std::endl;
        return;
    }

    // check destination cell and destination piece color
    if (map[destIndx] != nullptr && map[destIndx]->color() == map[curIndx]->color()) {
        std::cout << "there our piese" << std::endl;
        return;
    }

    // check destination cell and color for hit
    if (map[destIndx] != nullptr && map[destIndx]->color() != map[curIndx]->color()) {
        std::cout << map[destIndx]->color() << map[destIndx]->type() << " is dead!" << std::endl;
        delete map[destIndx];
    }

    map[curIndx]->move();
    map[destIndx] = map[curIndx];
    map[curIndx] = nullptr;

    m_player = m_player == 'W' ? 'B' : 'W';
}
