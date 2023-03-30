#include "LeaderboardDAO.h"
#include <string>
LeaderboardDAO::LeaderboardDAO()
{
	sql.ConnectToDB("savedata/leaderboard.db");
}

void LeaderboardDAO::setHighScore(int playerId, int score)
{
    std::string query = "INSERT INTO Player(id, high_score) VALUES(" + std::to_string(playerId) + ", " + std::to_string(score) + ")";
    sql.ExecuteQuery(query.c_str(), 0);
}

int LeaderboardDAO::getHighScore(int playerId)
{
    int score;
	std::string query = "SELECT high_score FROM Player WHERE id = " + std::to_string(playerId);
    sql.ExecuteQuery(query.c_str(), &score);
	return score;
}
