#pragma once
#include "../gen-cpp/Leaderboard.h"

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

namespace sas
{
	class LeaderboardClientCall
	{
	public:
		LeaderboardClientCall();
		~LeaderboardClientCall();

		void SetHighScore(int id, int highscore);
		void GetTop20();

	private:
		LeaderboardClient* m_Client;
		shared_ptr<TSocket> socket;
		shared_ptr<TTransport> transport;
		shared_ptr<TProtocol> protocol; 
		std::map<int32_t, int32_t> top20;
	};
}