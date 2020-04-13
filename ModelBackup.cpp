#include "ModelBackup.h"
#include "ChessModel.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include <fstream>
#include <iostream>

void ModelBackup::save(const ChessModel *model)
{
    std::ofstream file("save.txt");
    for (size_t i = 0; i < model->map.size(); i++) {
        unsigned char buff[] = "__";
        if (model->get(i) != nullptr) {
            buff[0] = model->get(i)->color();
            buff[1] = model->get(i)->type();
        }
        file << buff;
    }
    file << model->m_player;
    file.close();
}

void ModelBackup::load(ChessModel *model)
{
    std::ifstream file("save.txt");
    if (!file.is_open()) return;

    for (size_t i = 0; i < model->map.size(); i++) {
        delete model->map[i];
    }

    PieceGenerator piece;
    for (size_t i = 0; i < model->map.size(); i++) {
        unsigned char buff[2];
        file >> buff[0] >> buff[1];
        model->map[i] = piece.generate(buff[0], buff[1]);
    }
    file >> model->m_player;
    file.close();
}

Piece *PieceGenerator::generate(const unsigned char color, const unsigned char type)
{
    switch (type) {
    case 'Q': return new Queen(color);
    case 'K': return new King(color);
    case 'B': return new Bishop(color);
    case 'N': return new Knight(color);
    case 'R': return new Rook(color);
    case 'P': return new Pawn(color);
    default: return nullptr;
    }
}
