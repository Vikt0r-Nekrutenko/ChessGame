#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "gameboard.hpp"
#include "imodel.hpp"
#include "cursor.hpp"
#include "model.hpp"
#include "stackmodel.hpp"
#include "fields.hpp"

class GameModel;

class GameSaveModel : public stf::sdb::StackModel
{
public:
    GameSaveModel(GameModel *model);

    void save();
    void load();

    stf::sdb::IntVecField board = stf::sdb::IntVecField(this, BOARD_W * BOARD_H);
    stf::sdb::IntField    player = stf::sdb::IntField(this);

    GameModel *mModel;
};

class GameResultModel : public stf::sdb::Model
{
public:
    GameResultModel();

    void gameOverHandler(int winner, const stf::Vec2d& wins);;

    stf::sdb::DateTimeField gameTime = stf::sdb::DateTimeField(this);
    stf::sdb::IntField winner = stf::sdb::IntField(this);
    stf::sdb::IntField wWins = stf::sdb::IntField(this);
    stf::sdb::IntField bWins = stf::sdb::IntField(this);
};

class CastlingKing;

class GameModel : public stf::smv::BaseModel
{
public:
    GameSaveModel saves = GameSaveModel(this);
    GameResultModel results = GameResultModel();
    GameBoard mBoard = GameBoard();
    Cursor mCursor = Cursor();
    std::vector<Note> log;
    stf::ColorTable player = stf::ColorTable::White;

    GameModel();

    void reset();
    std::string playerName() const;
    std::string opponentName() const;
    TurnType findCastlingTurn();
    TurnType findAttackInPassigTurn();
    TurnType unavailiableTurnHandler(const GameBoard &backup, const stf::ColorTable col, const TurnType isCheckType);

    stf::smv::IView *put(stf::smv::IView *sender);
    stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) override;
};

#endif // GAMEMODEL_HPP
