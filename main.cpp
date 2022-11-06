#include <window.hpp>
#include <iostream>

class ViewedCell
{
public:
    virtual uint8_t view() const = 0;
};

class ColoredCell
{
public:
    virtual uint8_t color() const = 0;
};

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
    return Game().run();
}
