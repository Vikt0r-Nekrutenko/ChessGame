#include "ChessBoard.h"
#include "ChessModel.h"
#include "Pieces.h"
#include <iostream>

ChessBoard::ChessBoard()
{
    m_array.resize(m_w * m_h, ' ');

    int hCuted = m_h - 2;
    int wCuted = m_w - 1;

    int bottom = m_h - 3;
    int right  = m_w - 2;

    // draw net
    for (int y = 2; y < hCuted; y++) {
        for (int x = 1; x < wCuted; x++) {
            int indx = m_w * y + x;
            int xOffset = x + 2;

            if (y % 2 == 0) {
                m_array[indx] = 196;
            }
            if (xOffset % 3 == 0) {
                m_array[indx] = 179;
            }
            if (xOffset % 3 == 0 && y == 2) {
                m_array[indx] = 194;
            }
            else if (xOffset % 3 == 0 && y == bottom ) {
                m_array[indx] = 193;
            }
            else if (y % 2 == 0 && x == 1) {
                m_array[indx] = 195;
            }
            else if (y % 2 == 0 && x == right) {
                m_array[indx] = 180;
            }
            else if (xOffset % 3 == 0 && y % 2 == 0) {
                m_array[indx] = 197;
            }
        }
    }

    // draw corners
    m_array[m_w * 2 + 1] = 218;
    m_array[m_w * 2 + right] = 191;
    m_array[m_w * bottom + 1] = 192;
    m_array[m_w * bottom + right] = 217;

    // draw numbers on right & left side
    for (int i = 3, j = 1; i < bottom; i += 2, j++) {
        m_array[m_w * i + wCuted] = m_array[m_w * i] = '0' + j;
    }

    // draw letters on bottom & top side
    for (int i = 3, j = 1; i < right; i += 3, j++) {
        m_array[m_w + i] = m_array[m_w * hCuted + i] = 'a' + j - 1;
    }

    // draw text
    const char *whiteText = "White", *blackText = "Black";
    for (int i = 0; i < 5; i++) {
        m_array[(m_w / 2 - 2) + i] = whiteText[i];
        m_array[m_w * (m_h - 1) + ((m_w/2 - 2) + i)] = blackText[i];
    }
}

void ChessBoard::show()
{
    system("cls");

    int cellWidth = 3;
    int cellHeight = 2;
    int boardSize = 8;

    int modelIndex = 0;
    for (int y = 0; y < boardSize * cellHeight; y += cellHeight) {
        for (int x = 0; x < boardSize * cellWidth; x += cellWidth) {
            if (m_model->get(modelIndex) != nullptr) {
                m_array[m_w * (y + cellWidth) + (x + cellHeight)]     = m_model->get(modelIndex)->color();
                m_array[m_w * (y + cellWidth) + (x + cellHeight) + 1] = m_model->get(modelIndex)->type();
            }
            else {
                m_array[m_w * (y + cellWidth) + (x + cellHeight)] = ' ';
                m_array[m_w * (y + cellWidth) + (x + cellHeight) + 1] = ' ';
            }
            modelIndex++;
        }
    }

    for (int indx = 0; indx < m_w * m_h; indx++) {
        if (indx % m_w == 0) {
            std::cout << std::endl;
        }
        std::cout << m_array[indx];
    }
    std::cout << std::endl;
}

void ChessBoard::setModel(const ChessModel *model)
{
    m_model = model;
}
