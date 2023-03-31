
#include <iostream>
#include "LeaderboardClientCall.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;


namespace sas
{
	LeaderboardClientCall::LeaderboardClientCall()
	{
		socket = shared_ptr<TSocket>(new TSocket("localhost", 9090));
		transport = shared_ptr<TTransport>(new TBufferedTransport(socket));
		protocol = shared_ptr<TProtocol>(new TBinaryProtocol(transport));
		m_Client = new LeaderboardClient(protocol);
		transport->open();
	}
	LeaderboardClientCall::~LeaderboardClientCall()
	{
	}
	void LeaderboardClientCall::SetHighScore(int id, int highscore)
	{
		m_Client->setHighScore(id, highscore);
	}
	void LeaderboardClientCall::GetTop20()
	{
		m_Client->getTop20(top20);
		std::map<int32_t, int32_t>::iterator it;
		std::cout << "[PlayerID][Score]:" << std::endl;
		for (it = top20.begin(); it != top20.end(); it++) {
			std::cout << it->first << " " << it->second << std::endl;
		}
	}
}