#ifndef SERVERQUEUE_H_
#define SERVERQUEUE_H_

#include <string>
#include "Queue.h"

class ServerQueue {
public:
	ServerQueue(const std::string& archivo, const char letra);
	virtual ~ServerQueue();

	template<class T> void send(T dato);
	template<class T> void receive(const unsigned int type, T* dato);

	void create();
	void destroy();

private:
	Queue queue;
};

template<class T> void ServerQueue::send(T dato) {
	queue.send(dato);
}

template<class T> void ServerQueue::receive(const unsigned int type, T* buffer) {
	queue.receive(type, buffer);
}

#endif /* SERVERQUEUE_H_ */
