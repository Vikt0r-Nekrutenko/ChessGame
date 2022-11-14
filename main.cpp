#include <window.hpp>
#include <iostream>
#include <gameview.hpp>
#include "iview.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"

class Game : public stf::Window
{
public:
    GameModel gameModel = GameModel();
    MenuView menuView = MenuView(&gameModel);
    stf::smv::IView *currentView = &menuView;

    Game()
    {
        enableLog();
        stf::Renderer::log.setHeight(20);
        stf::Renderer::log.setX(renderer.Size.x - 15);
    }

    bool onUpdate(const float) final
    {
        currentView->show(renderer);
        return currentView->isContinue();
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
