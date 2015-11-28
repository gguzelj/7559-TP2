#include "Client.h"

Client::Client() :
		connectionQueue(utils::QUEUE_FILE, utils::QUEUE_FILE_CHAR),
		connectionId(0),
		log(Logger::LogLevel::DEBUG) {

}

Client::~Client() {
}

unsigned int Client::connect(){
	log.debug("Trying to connect to DbManager");

	if(connectionQueue.getQueue() == CONNECTION_ERROR){
		log.debug("Error while trying to connect with DbManager");
		return CONNECTION_ERROR;
	}

	sendConnectionRequest();
	receiveConnectionResponse();

	log.setName(Helper::convertToString(this->connectionId));

	return CONNECTION_OK;
}

void Client::sendConnectionRequest() {
	log.debug("Sending connection request");
	connectionRequest request;
	request.mtype = CONNECTION_REQUEST;
	request.clientUUID = getRandomUUID();
	connectionQueue.send(request);
}

void Client::receiveConnectionResponse() {
	log.debug("Receiving connection response");

	connectionResponse response;
	connectionQueue.receive(CONNECTION_RESPONSE, &response);

	if(response.result == CONNECTION_ERROR)
		perror("Unknown error while connecting server");

	this->connectionId = response.connectionId;
	log.debug("Connection established. Connection id: {}", response.connectionId);
}

long Client::getRandomUUID(){
	srand (time(NULL));
	return (static_cast<long>(rand()) << (sizeof(int) * 8)) | rand();
}

void Client::processInput(std::string input){


}
