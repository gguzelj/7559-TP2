#include "ClientQueue.h"

ClientQueue::ClientQueue(const std::string& archivo, const char letra) : queue(archivo, letra) {
}

ClientQueue::~ClientQueue() {
}

unsigned int ClientQueue::getQueue() {
	return queue.getQueue();
}
