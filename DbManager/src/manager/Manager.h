#ifndef MANAGER_H_
#define MANAGER_H_

#include <requests/DbRequest.h>
#include <queue/ServerQueue.h>
#include <utils/utils.h>

class Manager {
public:
	Manager();
	virtual ~Manager();

	void handleRequest();

	bool isRunning();

private:

	ServerQueue requestsQ;
	ServerQueue responsesQ;
	bool running;

	void handleNewConnectionRequest(const request request);
	void handleInsertRequest(const request request);
	void handleReadRequest(const request request);
	void handleSelectRequest(const request request);
	void handleShutDownRequest(const request request);

};

#endif /* MANAGER_H_ */
