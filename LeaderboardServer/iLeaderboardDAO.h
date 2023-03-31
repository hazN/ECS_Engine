#pragma once
#include <map>

class iLeaderboardDAO
{
public:
	iLeaderboardDAO() {}
	virtual ~iLeaderboardDAO() {}

	virtual void setHighScore(int playerId, int score) = 0;
	virtual int getHighScore(int playerId) = 0;
	virtual std::map<int, int> getTop20HighScores() = 0;
};
