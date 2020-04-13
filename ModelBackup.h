#ifndef MODELSAVER_H
#define MODELSAVER_H

class ChessModel;
class Piece;

class PieceGenerator
{
public:
    Piece *generate(const unsigned char color, const unsigned char type);
};

class ModelBackup
{
public:
    void save(const ChessModel *model);
    void load(ChessModel *model);
};

#endif // MODELSAVER_H
