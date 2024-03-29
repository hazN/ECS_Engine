#include "LeaderboardDAO.h"
#include <string>
namespace sas
{
    LeaderboardDAO::LeaderboardDAO()
    {
        sql.ConnectToDB("savedata/leaderboard.db");
    }

    void LeaderboardDAO::setHighScore(int playerId, int score)
    {
        int playerIdExists = 0;
        std::string query = "SELECT id FROM Player WHERE id = " + std::to_string(playerId);
        sql.ExecuteQuery(query.c_str(), &playerIdExists);

        // Update if it exists, insert if it doesn't
        if (playerIdExists > 0)
            query = "UPDATE Player SET high_score = " + std::to_string(score) + " WHERE id = " + std::to_string(playerId);
        else
            query = "INSERT INTO Player(id, high_score) VALUES(" + std::to_string(playerId) + ", " + std::to_string(score) + ")";
        sql.ExecuteQuery(query.c_str(), 0);
    }

    int LeaderboardDAO::getHighScore(int playerId)
    {
        int score;
        std::string query = "SELECT high_score FROM Player WHERE id = " + std::to_string(playerId);
        sql.ExecuteQuery(query.c_str(), &score);
        return score;
    }
}