#ifndef MANAGER_H_
#define MANAGER_H_

#include <requests/DbRequest.h>
#include <queue/ServerQueue.h>
#include <logger/Logger.h>
#include <utils/utils.h>

class Manager {
public:
	Manager();
	virtual ~Manager();

	void handleRequest();

private:

	ServerQueue requestsQueue;
	ServerQueue connectionQueue;
	Logger log;
	int connectionCounter;

	void handleNewConnectionRequest(const request request);
	void handleInsertRequest(const request request);
	void handleReadRequest(const request request);
	void handleSelectRequest(const request request);

};

#endif /* MANAGER_H_ */
