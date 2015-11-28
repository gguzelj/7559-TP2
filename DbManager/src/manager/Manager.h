#ifndef MANAGER_H_
#define MANAGER_H_

#include <queue/ServerQueue.h>
#include <logger/Logger.h>
#include <utils/utils.h>

class Manager {
public:
	Manager();
	virtual ~Manager();

private:

	ServerQueue queue;
	Logger log;

};

#endif /* MANAGER_H_ */
