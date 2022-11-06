#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include "cells.hpp"

class Player : public ColoredCell
{
public:
    virtual Player* opponent() const = 0;
};

class WhitePlayer : public Player
{
    Player* opponent() const override
    {
        return nullptr;
    }
};

class BlackPlayer : public Player
{
    Player* opponent() const override
    {
        return nullptr;
    }
};

#endif // PLAYERS_HPP
