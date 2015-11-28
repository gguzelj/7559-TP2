#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdlib>
#include <utils/utils.h>
#include <logger/Logger.h>
#include <queue/ClientQueue.h>
#include <requests/DbRequest.h>
#include <requests/DbResponse.h>

class Client {
public:
	Client();
	virtual ~Client();

	void processInput(std::string input);
	unsigned int connect();

private:
	Queue connectionQueue;
	long connectionId;
	Logger log;

	long getRandomUUID();
	void sendConnectionRequest();
	void receiveConnectionResponse();
};

#endif /* CLIENT_H_ */
