#include "ChessBoard.h"
#include "ChessModel.h"
#include "ModelBackup.h"
#include <iostream>
#include <cmath>

int main()
{
    ChessBoard board;
    ChessModel model;

    board.setModel(&model);

    char cx, cy, dx, dy;
    do {
        board.show();
        std::cout << model.getPlayer() << ": ";
        std::cin >> cx >> cy >> dx >> dy;
        if (cx == 's' && cy == 'a' && dx == 'v' && dy == 'e') {
            ModelBackup saver;
            saver.save(&model);
        }
        else if (cx == 'l' && cy == 'o' && dx == 'a' && dy == 'd') {
            ModelBackup loader;
            loader.load(&model);
        }
        else if (cx == 'r' && cy == 'e' && dx == 's' && dy == 't') {

        }
        else if (cx == 'e' && cy == 'x' && dx == 'i' && dy == 't') {
            break;
        }
        else {
            model.move(cx, cy, dx, dy);
        }
        system("pause");
    }
    while(true);
    return 0;
}
