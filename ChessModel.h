#ifndef CHESSMODEL_H
#define CHESSMODEL_H

#include <vector>

class Piece;

class ChessModel {
public:
    ChessModel();
    ~ChessModel();
    Piece *get(const int x, const int y);
    Piece *get(const int indx) const;
    bool coordIsValid(const int cX, const int cY, const int dX, const int dY) const;
    bool pieceIsJumping(int cX, int cY, const int dX, const int dY) const;
    void move(const int cX, const int cY, const int dX, const int dY);
private:
    std::vector<Piece *> map;
    const int N = 8;
    unsigned char m_player = 'W';
};

#endif // CHESSMODEL_H
