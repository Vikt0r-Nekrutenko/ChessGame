#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>

class ChessModel;

class ChessBoard {
public:
    ChessBoard();
    void show();
    void setModel(const ChessModel *model);
private:
    const int m_w = 27, m_h = 21;
    std::vector<unsigned char> m_array;
    const ChessModel *m_model = nullptr;
};
#endif // CHESSBOARD_H
