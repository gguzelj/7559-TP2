#ifndef QUEUE_H_
#define QUEUE_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "../requests/DbRequest.h"
#include "../requests/DbResponse.h"

class Queue {
private:
	key_t clave;
	int id;

public:
	Queue(const std::string& archivo, const char letra);
	virtual ~Queue();

	template<class T> void send(T dato);
	template<class T> void receive(const unsigned int type, T* dato);

	void create();
	unsigned int getQueue();
	void destroy();
};

template<class T> void Queue::send(T dato) {
	msgsnd(this->id, static_cast<const void*>(&dato), sizeof(T) - sizeof(long), 0);
}

template<class T> void Queue::receive(const unsigned int type, T* buffer) {
	msgrcv(this->id, static_cast<void *>(buffer), sizeof(T) - sizeof(long), type, 0);
}

#endif /* QUEUE_H_ */
