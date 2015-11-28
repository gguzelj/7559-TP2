#ifndef CLIENTQUEUE_H_
#define CLIENTQUEUE_H_

#include <string>
#include "Queue.h"

class ClientQueue {
public:
	ClientQueue(const std::string& archivo, const char letra);
	virtual ~ClientQueue();

	template<class T> void send(T dato);
	template<class T> void receive(const unsigned int type, T* dato);

	unsigned int getQueue();

private:
	Queue queue;
};

template<class T> void ClientQueue::send(T dato) {
	queue.send(dato);
}

template<class T> void ClientQueue::receive(const unsigned int type, T* buffer) {
	queue.receive(type, buffer);
}

#endif /* CLIENTQUEUE_H_ */
