#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include "cells.hpp"

class Player
{
public:
    virtual Player* opponent() const = 0;
    void *operator new(size_t size);
};

class WhitePlayer : public Player, public WhiteColoredCell
{
    Player* opponent() const override
    {
        return nullptr;
    }
};

class BlackPlayer : public Player, public BlackColoredCell
{
    Player* opponent() const override
    {
        return nullptr;
    }
};

namespace players {
static CellCreator<WhitePlayer> wPlayer = CellCreator<WhitePlayer>();
static CellCreator<BlackPlayer> bPlayer = CellCreator<BlackPlayer>();
}

#endif // PLAYERS_HPP
