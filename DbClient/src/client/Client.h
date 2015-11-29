#ifndef CLIENT_H_
#define CLIENT_H_

#include <sstream>
#include <cstdlib>
#include <utils/utils.h>
#include <logger/Logger.h>
#include <queue/ClientQueue.h>
#include <requests/DbRequest.h>
#include <requests/DbResponse.h>

using namespace std;

class Client {
public:
	Client();
	virtual ~Client();

	void processInput(string input);
	void processInsert(string input);
	void processRead(string input);

	unsigned int connect();

private:
	ClientQueue requestsQ;
	ClientQueue responsesQ;

	long sessionId;

	Logger log;

	void sendInsertRequest(string name, string address, string phone);
	void receiveInsertResponse();

	request createRequest(long type);
	insertRequest createInsertRequest(string name, string address, string phone);

	long getRandomUUID();
	bool openQueue(ClientQueue& queue);
	void printMessage(string msg);
};

#endif /* CLIENT_H_ */
