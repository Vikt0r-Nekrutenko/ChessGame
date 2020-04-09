#include "ChessBoard.h"
#include "ChessModel.h"
#include <iostream>
#include <cmath>

int main()
{
    ChessBoard cb1;
    ChessModel cm;

    cb1.setModel(&cm);

    char cx, cy, dx, dy;
    do {
        cb1.show();
        std::cin >> cx >> cy >> dx >> dy;
        if (cx == 's' && cy == 'a' && dx == 'v' && dy == 'e') {}
        else if (cx == 'l' && cy == 'o' && dx == 'a' && dy == 'd') {}
        else if (cx == 'r' && cy == 'e' && dx == 's' && dy == 't') {}
        else {
            cm.move(cx, cy, dx, dy);
            system("pause");
        }
    }
    while(true);
    return 0;
}
