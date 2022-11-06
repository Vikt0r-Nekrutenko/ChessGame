#include "players.hpp"

Player *WhitePlayer::opponent() const
{
    return players::bPlayer();
}

Player *BlackPlayer::opponent() const
{
    return players::wPlayer();
}
