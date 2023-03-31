#include "../gen-cpp/Leaderboard.h"

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <iostream>
#include "LeaderboardClient.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;


int LeaderboardClientCall() {

	shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	LeaderboardClient client(protocol);
	transport->open();
	std::map<int32_t, int32_t> top20;
	client.setHighScore(20, 500);
	client.setHighScore(25, 1000);
	client.setHighScore(300, 2000);
	client.getTop20(top20);

	std::map<int32_t, int32_t>::iterator it;
	std::cout << "[PlayerID][Score]:" << std::endl;
	for (it = top20.begin(); it != top20.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
	return 0;
}
