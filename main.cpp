#include <window.hpp>
#include <iostream>
#include "pawns.hpp"

class Game : public stf::Window
{
    bool onUpdate(const float) final
    {
        return true;
    }

    void keyEvents(const int key) final
    {

    }

    void mouseEvents(const stf::MouseRecord& mr) final
    {

    }
};

int main()
{
//    return Game().run();
    std::cout << (int)WPawn().color() << std::endl;
}
