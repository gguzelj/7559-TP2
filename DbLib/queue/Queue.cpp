#include "Queue.h"

Queue::Queue(const std::string& archivo, const char letra) : id(0) {
	this->clave = ftok(archivo.c_str(), letra);
	if (this->clave == -1)
		perror("Error en ftok");
}

Queue::~Queue() {
}


void Queue::create(){
	this->id = msgget(this->clave, 0777 | IPC_CREAT);
	if (this->id == -1)
		perror("Error en msgget");
}

unsigned int Queue::getQueue(){
	this->id = msgget(this->clave, 0);

	return (this->id == -1)?CONNECTION_ERROR:CONNECTION_OK;
}

void Queue::destroy(){
	msgctl(this->id, IPC_RMID, NULL);
}
