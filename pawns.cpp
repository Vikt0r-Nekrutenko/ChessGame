#include "pawns.hpp"
#include "gameboard.hpp"

#define WPAWN_SPAWN_Y 6
#define BPAWN_SPAWN_Y 1

#define WPASSING_ATTACK_Y 3
#define BPASSING_ATTACK_Y 4

uint8_t Pawn::view() const
{
    return 'P';
}

bool WPawn::isRightAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable)
{
    if(selectable != selected + stf::Vec2d{+1,-1})
        return false;
    if(selected.y != WPASSING_ATTACK_Y)
        return false;
    if(log.back().cell->uniqueView() != pieces::bPawn()->uniqueView())
        return false;
    if(log.back().from != stf::Vec2d{selected.x + 1, BPAWN_SPAWN_Y} && log.back().to != selected + stf::Vec2d{+1,0})
        return false;
    return true;
}

bool WPawn::isLeftAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable)
{
    if(selectable != selected + stf::Vec2d{-1,-1})
        return false;
    if(selected.y != WPASSING_ATTACK_Y)
        return false;
    if(log.back().cell->uniqueView() != pieces::bPawn()->uniqueView())
        return false;
    if(log.back().from != stf::Vec2d{selected.x - 1, BPAWN_SPAWN_Y} && log.back().to != selected + stf::Vec2d{-1,0})
        return false;
    return true;
}

bool Pawn::isRightAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable) { return false; }

bool Pawn::isLeftAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable) { return false; }

bool Pawn::isAttackInPassing(const GameBoard &board, const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable)
{
    if(!Pawn::canJump(board, selected, selectable))
        return false;
    if(!isLeftAttackInPassing(board,log,selected,selectable) && !isRightAttackInPassing(board,log,selected,selectable))
        return false;
    return true;
}

bool Pawn::canAttack(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return board[{selectable}]->getOpponent() == board[{selected}]->color() && noPiecesOnWay(board, selected, selectable);
}

bool Pawn::canJump(const GameBoard& board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    return board[selectable]->color() == cells::emptyCell()->color() && noPiecesOnWay(board, selected, selectable);
}

int WPawn::uniqueView() const
{
    return +1;
}

bool BPawn::isRightAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable)
{
    if(selectable != selected + stf::Vec2d{+1,+1})
        return false;
    if(selected.y != BPASSING_ATTACK_Y)
        return false;
    if(log.back().cell->uniqueView() != pieces::wPawn()->uniqueView())
        return false;
    if(log.back().from != stf::Vec2d{selected.x + 1, WPAWN_SPAWN_Y} && log.back().to != selected + stf::Vec2d{+1,0})
        return false;
    return true;
}

bool BPawn::isLeftAttackInPassing(const std::vector<Note> &log, const stf::Vec2d &selected, const stf::Vec2d &selectable)
{
    if(selectable != selected + stf::Vec2d{-1,+1})
        return false;
    if(selected.y != BPASSING_ATTACK_Y)
        return false;
    if(log.back().cell->uniqueView() != pieces::wPawn()->uniqueView())
        return false;
    if(log.back().from != stf::Vec2d{selected.x - 1, WPAWN_SPAWN_Y} && log.back().to != selected + stf::Vec2d{-1,0})
        return false;
    return true;
}

int BPawn::uniqueView() const
{
    return -1;
}

bool WPawn::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!Pawn::canJump(board, selected, selectable))
        return false;
    if(selectable - selected == stf::Vec2d(0, -1))
        return true;
    else if(selected.y == WPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, -2))
        return true;
    return false;
}

bool WPawn::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if((pos == stf::Vec2d(+1, -1) || pos == stf::Vec2d(-1, -1)) && Pawn::canAttack(board, selected, selectable)) {
        return true;
    } return false;
}

bool BPawn::canJump(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    if(!Pawn::canJump(board, selected, selectable))
        return false;
    if(selectable - selected == stf::Vec2d(0, +1))
        return true;
    else if(selected.y == BPAWN_SPAWN_Y && selectable - selected == stf::Vec2d(0, +2))
        return true;
    return false;
}

bool BPawn::canAttack(const GameBoard &board, const stf::Vec2d &selected, const stf::Vec2d &selectable) const
{
    const stf::Vec2d pos = selectable - selected;
    if((pos == stf::Vec2d(+1, +1) || pos == stf::Vec2d(-1, +1)) && Pawn::canAttack(board, selected, selectable)) {
        return true;
    } return false;
}
