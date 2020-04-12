#include "ChessModel.h"
#include "Pieces.h"
#include "ModelBackup.h"
#include <iostream>

enum class CastlingType {
    LEFT, RIGHT, NONE
};

ChessModel::ChessModel() {
    map.resize(m_N * m_N, nullptr);

//    for (int x = 0; x < m_N; x++) {
//        map[m_N + x] = new Pawn('W');
//        map[m_N * 6 + x] = new Pawn('B');
//    }

//    map[0] = new Rook('W');
//    map[m_N - 1] = new Rook('W');
//    map[m_N * 7] = new Rook('B');
//    map[m_N * 7 + 7] = new Rook('B');

//    map[1] = new Knight('W');
//    map[m_N - 2] = new Knight('W');
//    map[m_N * 7 + 1] = new Knight('B');
//    map[m_N * 7 + 6] = new Knight('B');

//    map[2] = new Bishop('W');
//    map[m_N - 3] = new Bishop('W');
//    map[m_N * 7 + 2] = new Bishop('B');
//    map[m_N * 7 + 5] = new Bishop('B');

    map[3] = new King('W');
    map[m_N * 7 + 3] = new King('B');

    map[4] = new Queen('W');
    map[m_N * 7 + 4] = new Queen('B');
}

ChessModel::~ChessModel()
{
    for (int i = map.size() - 1; i >= 0; i--) {
        delete map[i];
    }
}

Piece *ChessModel::get(const int x, const int y)
{
    return map[m_N * y + x];
}

Piece *ChessModel::get(const int indx) const
{
    return map[indx];
}

void ChessModel::castling(const int curIndx, const int destIndx, const CastlingType type)
{
    // king motion
    map[curIndx]->move();
    map[destIndx] = map[curIndx];
    map[curIndx] = nullptr;

    if (type == CastlingType::RIGHT) {
        // rook motion
        map[destIndx + 2]->move();
        map[destIndx - 1] = map[destIndx + 2];
        map[destIndx + 2] = nullptr;

        std::cout << "long castling" << std::endl;
    }
    else if (type == CastlingType::LEFT) {
        // rook motion
        map[destIndx - 1]->move();
        map[destIndx + 1] = map[destIndx - 1];
        map[destIndx - 1] = nullptr;

        std::cout << "short castling" << std::endl;
    }
}

CastlingType ChessModel::castlingIsPossible(const int cX, const int cY, const int dX, const int dY) const
{
    int curIndx = m_N * cY + cX;
    int destIndx = m_N * dY + dX;

    Piece *king = map[curIndx];
    Piece *rookRight = map[destIndx + 2];
    Piece *rookLeft = map[destIndx - 1];

    if (king->type() == 'K' && king->moves() == 0) {
        if (rookRight != nullptr && rookRight->type() == 'R' && rookRight->moves() == 0) {
            for (int i = curIndx + 1; i <= destIndx + 1; i++) {
                if (map[i] != nullptr) {
                    return CastlingType::NONE;
                }
            }
            return CastlingType::RIGHT;
        } else if (rookLeft != nullptr && rookLeft->type() == 'R' && rookLeft->moves() == 0) {
            for (int i = curIndx - 1; i >= destIndx; i--) {
                if (map[i] != nullptr) {
                    return CastlingType::NONE;
                }
            }
            return CastlingType::LEFT;
        }
    }
    return CastlingType::NONE;
}

void ChessModel::pawnTransformation()
{
    for (int j = 0; j < m_N; j += 7) {
        for (int i = 0; i < m_N; i++) {
            if (map[m_N * j + i] != nullptr && map[m_N * j + i]->type() == 'P') {
                unsigned char pieces[] = "QRBN";
                unsigned char color = map[m_N * j + i]->color();

                delete map[m_N * j + i];
                PieceGenerator gen;
                map[m_N * j + i] = gen.generate(color, pieces[rand()%4]);
            }
        }
    }
}

bool ChessModel::isCheckmate(const int destIndx) const
{
    if (map[destIndx]->type() == 'K') {
        const char *playerName = (m_player == 'W') ? "White" : "Black";
        std::cout << playerName << " win. Checkmate!" << std::endl;
        return true;
    }
    return false;
}

bool ChessModel::isCheck(const int destIndx) const
{
    unsigned char opponent = m_player == 'W' ? 'B' : 'W';
    int kingX = 0, kingY = 0;
    for (size_t i = 0; i < map.size(); i++) {
        if (map[i] != nullptr && map[i]->color() == opponent && map[i]->type() == 'K') {
            kingX = i % m_N;
            kingY = i / m_N;
        }
    }

    int x = destIndx % m_N, y = destIndx / m_N;
    if (map[destIndx]->motionIsValid(x, y, kingX, kingY, nullptr) && pieceCanJumpTo(x, y, kingX, kingY)) {
        return true;
    }
    return false;
}

bool ChessModel::coordIsValid(const int cX, const int cY, const int dX, const int dY) const
{
    if ((cX >= 'a' && cX <= 'h' && cY >= '1' && cY <= '8') && (dX >= 'a' && dX <= 'h' && dY >= '1' && dY <= '8')) {
        return true;
    }
    return false;
}

bool ChessModel::pieceCanJumpTo(int cX, int cY, const int dX, const int dY) const
{
    int X = abs(dX - cX), Y = abs(dY - cY);
    int _X = dX - cX;
    _X = (_X == 0) ? 0 : _X / X;

    int _Y = dY - cY;
    _Y = (_Y == 0) ? 0 : _Y / Y;

    int lim = (X > Y ? X : Y) - 1;

    for (int i = 0; i < lim; i++) {
        if (map[m_N * (cY += _Y) + (cX += _X)] != nullptr) {
            return false;
        }
    }
    return true;
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

    int curIndx = m_N * cy + cx;
    int destIndx = m_N * dy + dx;

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

    CastlingType type = castlingIsPossible(cx, cy, dx, dy);
    if (type != CastlingType::NONE) {
        castling(curIndx, destIndx, type);
        return;
    }

    // check motion
    if (!map[curIndx]->motionIsValid(cx, cy, dx, dy, map[destIndx])) {
        std::cout << "not allowed" << std::endl;
        return;
    }

    // check jumping
    if (!map[curIndx]->canJump() && !pieceCanJumpTo(cx, cy, dx, dy)) {
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
        if (isCheckmate(destIndx)) {
            m_movesIsPossible = false;
            return;
        }
        delete map[destIndx];
    }

    map[curIndx]->move();
    map[destIndx] = map[curIndx];
    map[curIndx] = nullptr;

    pawnTransformation();

    if (isCheck(destIndx)) {
        const char *playerName = (m_player == 'W') ? "White" : "Black";
        const char *opponentName = (m_player == 'W') ? "Black" : "White";
        std::cout << playerName << " attacked the " << opponentName << " king. Check!" << std::endl;
    }
    m_player = m_player == 'W' ? 'B' : 'W';
}

int ChessModel::getN() const
{
    return m_N;
}

const char *ChessModel::getPlayer() const
{
    return (m_player == 'W') ? "White" : "Black";
}

bool ChessModel::movesIsPossible() const
{
    return m_movesIsPossible;
}
