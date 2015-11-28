#include "Manager.h"

Manager::Manager() :
		requestsQueue(utils::QUEUE_FILE, utils::REQUEST_QUEUE),
		connectionQueue(utils::QUEUE_FILE, utils::CONNECTION_QUEUE),
		log(Logger::LogLevel::DEBUG, "DB_MANAGER"),
		connectionCounter(0){

	log.debug("Creating DbManager");

	log.debug("Creating requests Queue");
	requestsQueue.create();

	log.debug("Creating connections Queue");
	connectionQueue.create();

	log.debug("All queues created");
	log.debug("DbManager created");
}

Manager::~Manager() {
	log.debug("Deleting DbManager");

	log.debug("Deleting requests Queue");
	requestsQueue.destroy();

	log.debug("Deleting connections Queue");
	connectionQueue.destroy();

	log.debug("All queues Deleted");
	log.debug("DbManager Deleted");
}

void Manager::handleRequest(){

	log.debug("Waiting for requests");

	request request;
	requestsQueue.receive(0, &request);

	log.info("New request from {}", request.connectionId);

	switch (request.typeRequest) {
		case NEW_CONNECTION:
			handleNewConnectionRequest(request);
		case INSERT:
			handleInsertRequest(request);
		case READ:
			handleReadRequest(request);
		case SELECT:
			handleSelectRequest(request);
			break;
		default:
			log.error("Unknown type of request");
	}

}

void Manager::handleNewConnectionRequest(const request newConnectionRequest){
	log.info("Creating a new connectionId for new connection");
	connectionCounter++;

	newConnectionResponse response;

	response.mtype = newConnectionRequest.connectionId;
	response.connectionId = connectionCounter;
	response.result = CONNECTION_OK;

	log.info("Assigning connection id {} to new connection", connectionCounter);

	connectionQueue.send(response);
}

void Manager::handleInsertRequest(const request insertRequest){

}

void Manager::handleReadRequest(const request readRequest){

}

void Manager::handleSelectRequest(const request selectRequest){

}
