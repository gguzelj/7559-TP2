#include "ServerQueue.h"

ServerQueue::ServerQueue(const std::string& archivo, const char letra) : queue(archivo, letra){
}

ServerQueue::~ServerQueue() {
}

void ServerQueue::create(){
	queue.create();
}

void ServerQueue::destroy(){
	queue.destroy();
}
