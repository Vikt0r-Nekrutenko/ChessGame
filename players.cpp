#include "players.hpp"


void *Player::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}

Player *WhitePlayer::opponent() const
{
    return players::bPlayer();
}

Player *BlackPlayer::opponent() const
{
    return players::wPlayer();
}
