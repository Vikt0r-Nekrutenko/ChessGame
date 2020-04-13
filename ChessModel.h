#ifndef CHESSMODEL_H
#define CHESSMODEL_H

#include <vector>

class Piece;
enum class CastlingType;

class ChessModel {
    friend class ModelBackup;
public:
    ChessModel();
    ~ChessModel();
    Piece *get(const int indx) const;
    CastlingType castlingIsPossible(const int cX, const int cY, const int dX, const int dY) const;
    void castling(const int curIndx, const int destIndx, const CastlingType type);
    void pawnTransformation();

    bool movesIsPossible() const;
    bool isCheckmate(const int destIndx) const;
    bool isCheck(const int destIndx) const;
    bool coordIsValid(const int cX, const int cY, const int dX, const int dY) const;
    bool pieceCanJumpTo(int cX, int cY, const int dX, const int dY) const;

    void move(const int cX, const int cY, const int dX, const int dY);
    int getN() const;
    const char *getPlayer() const;

private:
    std::vector<Piece *> map;
    const int m_N = 8;
    bool m_movesIsPossible = true;
    unsigned char m_player = 'W';
};

#endif // CHESSMODEL_H
