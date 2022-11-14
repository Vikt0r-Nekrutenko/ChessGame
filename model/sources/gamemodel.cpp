#include "gamemodel.hpp"
#include "endview.hpp"
#include "kings.hpp"
#include "pausemenuview.hpp"
#include "pawns.hpp"


GameSaveModel::GameSaveModel(GameModel *model)
    : stf::sdb::StackModel("chess_saves.sdb"), mModel(model) {}

void GameSaveModel::save()
{
    for(size_t i = 0; i < mModel->mBoard.mBoard.size(); ++i) {
        board[i] = mModel->mBoard.mBoard.at(i)->uniqueView();
    }
    player = (int)mModel->player;

    push<GameSaveModel>();
}

void GameSaveModel::load()
{
    pop<GameSaveModel>();

    for(size_t i = 0; i < mModel->mBoard.mBoard.size(); ++i) {
        int uniqueIndx = board[i];
        mModel->mBoard.place(i, mModel->mBoard.Pieces[uniqueIndx]);
    }
    mModel->player = (stf::ColorTable)player();
}

GameResultModel::GameResultModel()
    : stf::sdb::Model("chess_results.sdb") {}

void GameResultModel::gameOverHandler(int winner, const stf::Vec2d &wins){
    gameTime = stf::Time(nullptr);
    wWins = wWins() + wins.x;
    bWins = bWins() + wins.y;
    this->winner = winner;
}

GameModel::GameModel()
{
    try {
        results.load(results.header().size - 1);
    } catch(...) { }

    log.push_back({cells::emptyCell(), {0,0}, {0,0}, TurnType::Nothing});
}

void GameModel::reset()
{
    mCursor.reset();
    mBoard = GameBoard();
    player = stf::ColorTable::White;

    log.clear();
    log.push_back({cells::emptyCell(), {0,0}, {0,0}, TurnType::Nothing});
}

std::string GameModel::playerName() const
{
    return player == stf::ColorTable::White ? "White" : "Black";
}

TurnType GameModel::unavailiableTurnHandler(const GameBoard &backup, const stf::ColorTable col, const TurnType isCheckType)
{
    if(player == col) {
        mBoard = backup;
        return TurnType::Unavailiable;
    } else return isCheckType;
}

TurnType GameModel::findCastlingTurn()
{
    if(mCursor.selectedCell.cell->view() != King().view())
        return TurnType::Nothing;

    CastlingKing *king = dynamic_cast<CastlingKing*>(mCursor.selectedCell.cell);

    TurnType longC  = mBoard.longCastling(mCursor, king, log);
    TurnType shortC = mBoard.shortCastling(mCursor, king, log);

    return longC == TurnType::LongCastling
            ? longC
            : shortC;
}

TurnType GameModel::findAttackInPassigTurn()
{
    if(mCursor.selectedCell.cell->view() == Pawn().view())
        return mBoard.isAttackInPassingAvailiable(mCursor, log);
    return TurnType::Nothing;
}

stf::smv::IView *GameModel::put(stf::smv::IView *sender)
{
    TurnType turn = TurnType::Nothing;
    GameBoard backup = mBoard;

    turn = findCastlingTurn();
    if(turn == TurnType::Nothing)
        turn = mBoard.makeTurn(mCursor);

    if(turn == TurnType::Nothing)
        turn = findAttackInPassigTurn();

    mBoard.transformPawns();

    TurnType bIsCheckW = mBoard.blackCheckToWhite();
    if(bIsCheckW == TurnType::BCheckToW)
        turn = unavailiableTurnHandler(backup, stf::ColorTable::White, bIsCheckW);

    TurnType wIsCheckB = mBoard.whiteCheckToBlack();
    if(wIsCheckB == TurnType::WCheckToB)
        turn = unavailiableTurnHandler(backup, stf::ColorTable::Red, wIsCheckB);

    if(turn != TurnType::Nothing)
        log.push_back({ mCursor.selectedCell.cell, mCursor.selectedCell.pos, mCursor.selectableCell.pos, turn });

    stf::Renderer::log << stf::endl <<
                          char(log.back().cell->view()) <<
                          char(log.back().from.x + 'a') << std::abs(log.back().from.y - BOARD_H) <<
                          cells::Turns[log.back().type] <<
                          char(log.back().to.x + 'a') << std::abs(log.back().to.y - BOARD_H);
    mCursor.reset();
    if(turn != TurnType::Nothing && turn != TurnType::Unavailiable)
        player = player == stf::ColorTable::White ? stf::ColorTable::Red : stf::ColorTable::White;

    if(mBoard.isCheckmate(player) || mBoard.possibleMovesExitst() == false) {
        if(player == stf::ColorTable::White)
            results.gameOverHandler((int)stf::ColorTable::White, {1,0});
        else if(player == stf::ColorTable::Red)
            results.gameOverHandler((int)stf::ColorTable::Red, {0,1});
        results.save();
        return new EndView(this);
    }

    return sender;
}

stf::smv::IView *GameModel::keyEventsHandler(stf::smv::IView *sender, const int key)
{
    switch (key)
    {
    case 'w':
        if(mCursor.selectableCell.pos.y > 0)
            mCursor.selectableCell.pos.y -= 1;
        else
            mCursor.selectableCell.pos.y = mBoard.Size.y - 1;
        break;

    case 'a':
        if(mCursor.selectableCell.pos.x > 0)
            mCursor.selectableCell.pos.x -= 1;
        else
            mCursor.selectableCell.pos.x = mBoard.Size.x - 1;
        break;

    case 's':
        if(mCursor.selectableCell.pos.y < mBoard.Size.y-1)
            mCursor.selectableCell.pos.y += 1;
        else
            mCursor.selectableCell.pos.y = 0;
        break;

    case 'd':
        if(mCursor.selectableCell.pos.x < mBoard.Size.x-1)
            mCursor.selectableCell.pos.x += 1;
        else
            mCursor.selectableCell.pos.x = 0;
        break;

    case 'q':
        return new PauseMenuView(this);
        break;

    case 'f':
        player = player == stf::ColorTable::White ? stf::ColorTable::Red : stf::ColorTable::White;
        break;

    case ' ':
        if(mCursor.isValidForSelect(mBoard[mCursor.selectableCell.pos], player)) {
            mCursor.select(mBoard[{mCursor.selectableCell.pos}]);
        } else if(mCursor.isValidForPut()) {
            return put(sender);
        }
    }
    return sender;
}
