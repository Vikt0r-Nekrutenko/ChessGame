#include <window.hpp>
#include <iostream>
#include "iview.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"

class Game : public stf::Window
{
public:
    GameModel gameModel = GameModel();
    MenuView gameView = MenuView(&gameModel);
    stf::smv::IView *currentView = &gameView;

    Game()
    {
        enableLog();
        stf::Renderer::log.setHeight(20);
        stf::Renderer::log.setX(30);
    }

    bool onUpdate(const float) final
    {
        currentView->show(renderer);
        return true;
    }

    void keyEvents(const int key) final
    {
        currentView = currentView->keyEventsHandler(key);
    }

    void mouseEvents(const stf::MouseRecord& mr) final
    {
        currentView = currentView->mouseEventsHandler(mr);
    }
};

int main()
{
    return Game().run();
}
