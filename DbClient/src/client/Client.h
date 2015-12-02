#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <utils/utils.h>
#include <queue/ClientQueue.h>
#include <requests/DbRequest.h>
#include <requests/DbResponse.h>
#include "InstructionHandler.h"

using namespace std;

class Client {
public:
	Client();
	virtual ~Client();

	void processFile(string file);
	void processInput(istream& input);
	void processInput(string input);

	void processInsert(string input);
	void processSelect(string input);
	void processShutDown(string input);

	unsigned int connect();

	bool isClosed();
private:

	ClientQueue requestsQ;
	ClientQueue responsesQ;

	long sessionId;

	InstructionHandler handler;

	bool closed;

	void sendInsertRequest(string input);
	void receiveInsertResponse();

	bool openQueue(ClientQueue& queue);
};

#endif /* CLIENT_H_ */
