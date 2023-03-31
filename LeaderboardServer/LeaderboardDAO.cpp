#include "LeaderboardDAO.h"
#include <string>

    LeaderboardDAO::LeaderboardDAO()
    {
        sql.ConnectToDB("leaderboard.db");
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
        sql.ExecuteQuery(query.c_str(), &playerIdExists);
    }

    int LeaderboardDAO::getHighScore(int playerId)
    {
        int score;
        std::string query = "SELECT high_score FROM Player WHERE id = " + std::to_string(playerId);
        sql.ExecuteQuery(query.c_str(), &score);
        return score;
    }

    std::map<int, int> LeaderboardDAO::getTop20HighScores()
    {
        std::vector<int> ids;
        std::vector<int> scores;
        std::string query = "SELECT id FROM Player ORDER BY high_score DESC LIMIT 20";
        sql.ExecuteQuery(query.c_str(), &ids);
        query = "SELECT high_score FROM Player ORDER BY high_score DESC LIMIT 20";
        sql.ExecuteQuery(query.c_str(), &scores);
        std::map<int, int> high_scores;
        for (size_t i = 0; i < ids.size(); i++)
        {
            high_scores.emplace(ids[i], scores[i]);
        }
        return high_scores;
    }