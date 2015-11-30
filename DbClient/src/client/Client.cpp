#include "Client.h"

Client::Client() :
		requestsQ(utils::QUEUE_FILE, utils::REQUESTS_QUEUE),
		responsesQ(utils::QUEUE_FILE, utils::RESPONSES_QUEUE),
		sessionId(Helper::getRandomUUID()),
		handler(sessionId),
		closed(false){
}

Client::~Client() {
}

unsigned int Client::connect(){
	Helper::printClientMsg("Connecting with DbManager");

	if( !openQueue(requestsQ) || !openQueue(responsesQ) ) {
		Helper::printClientMsg("No DbManager found");
		return CONNECTION_ERROR;
	}

	Helper::printClientMsg("Connection established!");
	Helper::printClientMsg();
	return CONNECTION_OK;
}

void Client::processFile(string path) {
	string line;
	ifstream file(path);
	if (file.is_open()) {
		while (getline(file, line))
			processInput(line);
		file.close();
	}
}

void Client::processInput(istream& input){
	string instruction;
	getline(input, instruction);
	processInput(instruction);
	Helper::printClientMsg();
	return;
}

void Client::processInput(string input){

	switch (handler.getTypeRequest(input)) {
		case RequestEnum::INSERT:
			return processInsert(input);

		case RequestEnum::READ:
			return processRead(input);

		case RequestEnum::SELECT:
			return processSelect(input);

		case RequestEnum::SHUT_DOWN:
			return processShutDown(input);

		case RequestEnum::UNKNOWN:
			if(handler.isExitInstruction(input)){
				closed = true;
				return;
			}
		default:
			Helper::printClientMsg("Unknown instruction");
	}

}

void Client::processInsert(string input){
	sendInsertRequest(input);
	receiveInsertResponse();
}

void Client::sendInsertRequest(string input){
	requestsQ.send(handler.createRequest(RequestEnum::INSERT));
	requestsQ.send(handler.createInsertRequest(input));
}

void Client::receiveInsertResponse(){
	insertResponse response;
	responsesQ.receive(this->sessionId, &response);

	if(response.result == INSERT_OK){
		Helper::printClientMsg("1 Record inserted");
	} else {
		Helper::printClientMsg("Error while inserting!");
	}
}

void Client::processRead(string input){

}

void Client::processSelect(string input){

}

void Client::processShutDown(string input){
	requestsQ.send(handler.createRequest(RequestEnum::SHUT_DOWN));
	requestsQ.send(handler.createShutDownRequest());

	shutDownResponse response;
	responsesQ.receive(this->sessionId, &response);
	closed = response.success;
}

bool Client::openQueue(ClientQueue& queue){
	return queue.getQueue() == CONNECTION_OK;
}

bool Client::isClosed(){
	return closed;
}
