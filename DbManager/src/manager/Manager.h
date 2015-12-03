#ifndef MANAGER_H_
#define MANAGER_H_

#include <persistence/EntityManager.h>
#include <Signals/EventHandler.h>
#include <Signals/SignalHandler.h>
#include <requests/DbRequest.h>
#include <queue/ServerQueue.h>
#include <utils/utils.h>
#include <list>

class Manager : public EventHandler {
public:
	Manager();
	virtual ~Manager();

	void handleRequest();

	bool isRunning();

	virtual int handleSignal(int signum) {
		std::cout << "SIGINT SIGNAL ARRIVED! Releasing resources" << std::endl;
		running = false;
		releaseResources();
		exit(signum);
	}

private:

	ServerQueue requestsQ;
	ServerQueue responsesQ;
	EntityManager entities;
	bool running;

	void handleNewConnectionRequest(const request request);
	void handleInsertRequest(const request request);
	void handleSelectRequest(const request request);
	void handleShutDownRequest();
	void releaseResources();

};

#endif /* MANAGER_H_ */
