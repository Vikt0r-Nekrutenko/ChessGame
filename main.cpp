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
    virtual stf::ColorTable color() const = 0;
};

class UniqueIntViewedCell
{
public:
    virtual int uniqueView() const = 0;
};

class BoardCell : public ColoredCell, public ViewedCell, public UniqueIntViewedCell
{
public:
};

class EmptyCell : public ColoredCell, public ViewedCell, public UniqueIntViewedCell
{
public:
    uint8_t view() const override { return ' '; }
    stf::ColorTable color() const override { return stf::ColorTable::Default; }
    int uniqueView() const override { return 0; }
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
