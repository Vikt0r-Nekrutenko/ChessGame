#include "ChessBoard.h"
#include "ChessModel.h"
#include "ModelBackup.h"
#include <iostream>
#include <cmath>

int main()
{
    ChessBoard *board = new ChessBoard;
    ChessModel *model = new ChessModel;

    board->setModel(model);

    char cx, cy, dx, dy;
    do {
        board->show();
        std::cout << "Type the following command:\n"
                     "1.save\n"
                     "2.load\n"
                     "3.restart/rest\n"
                     "4.exit\n"
                     "5.number of current cell & destination cell (a1 h8)\n"
                  << model->getPlayer() << ": ";
        std::cin >> cx >> cy >> dx >> dy;
        if (cx == 's' && cy == 'a' && dx == 'v' && dy == 'e') {
            ModelBackup saver;
            saver.save(model);
        }
        else if (cx == 'l' && cy == 'o' && dx == 'a' && dy == 'd') {
            ModelBackup loader;
            loader.load(model);
        }
        else if (cx == 'r' && cy == 'e' && dx == 's' && dy == 't') {
            delete model;
            model = new ChessModel;
			board->setModel(model);
        }
        else if (cx == 'e' && cy == 'x' && dx == 'i' && dy == 't') {
            break;
        }
        else {
            if (model->movesIsPossible()) {
                model->move(cx, cy, dx, dy);
            }
            else {
                std::cout << "Game ended. Type Restart." << std::endl;
            }
        }
//        system("pause");
    }
    while(true);

    delete board;
    delete model;

    return 0;
}
