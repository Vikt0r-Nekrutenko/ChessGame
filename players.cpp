#include "players.hpp"


void *Player::operator new(size_t size)
{
    return CellAllocator::cellAllocator.allocate(size);
}
