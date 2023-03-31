#pragma once
namespace sas
{
	class iLeaderboardDAO
	{
	public:
		iLeaderboardDAO() {}
		virtual ~iLeaderboardDAO() {}

		virtual void setHighScore(int playerId, int score) = 0;
		virtual int getHighScore(int playerId) = 0;
	};
}