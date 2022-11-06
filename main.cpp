#include <window.hpp>
#include <iostream>
#include "model.hpp"

class CellAllocator
{
public:
    static stf::sdb::DynamicFieldsAllocator cellAllocator;
};

stf::sdb::DynamicFieldsAllocator CellAllocator::cellAllocator = stf::sdb::DynamicFieldsAllocator();

template<class T>
class CellCreator
{
public:
    T* operator ()()
    {
        return cell = cell == nullptr ? new T() : cell;
    }

    T *cell = nullptr;
};

class ViewedCell
{
public:
    virtual uint8_t view() const = 0;

    void *operator new(size_t size)
    {
        return CellAllocator::cellAllocator.allocate(size);
    }
};

class ColoredCell
{
public:
    virtual stf::ColorTable color() const = 0;

    void *operator new(size_t size)
    {
        return CellAllocator::cellAllocator.allocate(size);
    }
};

class UniqueIntViewedCell
{
public:
    virtual int uniqueView() const = 0;

    void *operator new(size_t size)
    {
        return CellAllocator::cellAllocator.allocate(size);
    }
};

class BoardCell : public ColoredCell, public ViewedCell, public UniqueIntViewedCell
{
public:
    void *operator new(size_t size)
    {
        return CellAllocator::cellAllocator.allocate(size);
    }
};

class EmptyCell : public BoardCell
{
public:
    uint8_t view() const override { return ' '; }
    stf::ColorTable color() const override { return stf::ColorTable::Default; }
    int uniqueView() const override { return 0; }
};

class Player : public ColoredCell
{
public:
    virtual Player* opponent() const = 0;
};

class WhitePlayer : public Player
{
    Player* opponent() const override { return nullptr; }
};

class BlackPlayer : public Player
{
    Player* opponent() const override { return nullptr; }
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
