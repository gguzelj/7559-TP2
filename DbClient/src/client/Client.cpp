#include "Client.h"

Client::Client() :
		requestsQueue(utils::QUEUE_FILE, utils::REQUEST_QUEUE),
		connectionQueue(utils::QUEUE_FILE, utils::CONNECTION_QUEUE),
		connectionId(0),
		log(Logger::LogLevel::DEBUG) {

}

Client::~Client() {
}

unsigned int Client::connect(){
	log.debug("Trying to connect to DbManager");

	if( (requestsQueue.getQueue() == CONNECTION_ERROR) ||
		(connectionQueue.getQueue() == CONNECTION_ERROR)){
		log.debug("Error while trying to connect with DbManager");
		return CONNECTION_ERROR;
	}

	sendConnectionRequest();
	receiveConnectionResponse();

	return CONNECTION_OK;
}

void Client::sendConnectionRequest() {
	this->connectionId = getRandomUUID();

	log.debug("Sending connection request");
	request request;
	request.mtype = NEW_CONNECTION;
	request.connectionId = this->connectionId;
	request.typeRequest = NEW_CONNECTION;
	requestsQueue.send(request);
}

void Client::receiveConnectionResponse() {
	log.debug("Receiving connection response");

	newConnectionResponse response;
	connectionQueue.receive(this->connectionId, &response);

	if(response.result == CONNECTION_ERROR){
		perror("Unknown error while connecting server");
		log.error("Unknown error while connecting server");
	}

	this->connectionId = response.connectionId;
	log.setName(string("CLIENT-").append(Helper::convertToString(this->connectionId)));
	log.info("Connection established. Connection id: {}", response.connectionId);
}

long Client::getRandomUUID(){
	srand (time(NULL));
	return (static_cast<long>(rand()) << 8) | rand();
}

std::string Client::processInput(std::string input){



	return "" ;
}
