#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>

class ChessBoard {
public:
    ChessBoard();
    void show();
private:
    const int m_w = 27, m_h = 21;
    std::vector<unsigned char> m_array;
};
#endif // CHESSBOARD_H
