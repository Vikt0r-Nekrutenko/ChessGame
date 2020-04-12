#ifndef CHESSMODEL_H
#define CHESSMODEL_H

#include <vector>

class Piece;

class ChessModel {
    friend class ModelBackup;
public:
    ChessModel();
    ~ChessModel();
    Piece *get(const int x, const int y);
    Piece *get(const int indx) const;
    void pawnTransformation();
    bool coordIsValid(const int cX, const int cY, const int dX, const int dY) const;
    bool pieceIsJumping(int cX, int cY, const int dX, const int dY) const;
    void move(const int cX, const int cY, const int dX, const int dY);
    int getN() const;
    unsigned char getPlayer() const;

private:
    std::vector<Piece *> map;
    const int m_N = 8;
    unsigned char m_player = 'W';
};

#endif // CHESSMODEL_H
