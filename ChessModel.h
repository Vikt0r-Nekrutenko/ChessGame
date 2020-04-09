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
    const int N = 8;
    std::vector<Piece *> map;
};

#endif // CHESSMODEL_H
