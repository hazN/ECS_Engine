#pragma once
#include "iLeaderboardDAO.h"
#include "SQLiteDBHelper.h"

class LeaderboardDAO : public iLeaderboardDAO
{
public:
    LeaderboardDAO();

    virtual void setHighScore(int playerId, int score) override;

    virtual int getHighScore(int playerId) override;

private:
    SQLiteDBHelper sql;
};
