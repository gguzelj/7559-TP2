#include "Client.h"

Client::Client() :
		requestsQ(utils::QUEUE_FILE, utils::REQUESTS_QUEUE),
		responsesQ(utils::QUEUE_FILE, utils::RESPONSES_QUEUE),
		sessionId(getRandomUUID()),
		log(Logger::LogLevel::DEBUG),
		closed(false){
}

Client::~Client() {
}

void Client::printMessage(string msg) {
	cout << "Client > " << msg << std::endl;
}

unsigned int Client::connect(){
	printMessage("Connecting with DbManager");

	if( !openQueue(requestsQ) || !openQueue(responsesQ) ) {
		printMessage("No DbManager found");
		return CONNECTION_ERROR;
	}

	printMessage("Connection established!");
	return CONNECTION_OK;
}

long Client::getRandomUUID(){
	srand (time(NULL));
	return static_cast<long>(rand());
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
	return processInput(instruction);
}

void Client::processInput(string input){

	switch (InstructionHandler::getTypeRequest(input)) {
		case RequestEnum::INSERT:
			return processInsert(input);

		case RequestEnum::READ:
			return processRead(input);

		case RequestEnum::SELECT:
			return processSelect(input);

		case RequestEnum::SHUT_DOWN:
			return processShutDown(input);

		case RequestEnum::UNKNOWN:
			closed = InstructionHandler::isExitInstruction(input);
			break;

		default:
			Helper::printClientMsg("Unknown instruction");
	}

}

void Client::processInsert(string input){
	std::istringstream ss(input.substr(7));

	string name; getline(ss, name, ',');
	string address; getline(ss, address, ',');
	string phone; getline(ss, phone, ',');

	log.info("Trying to insert name {}, address {}, phone {}", name, address, phone);

	sendInsertRequest(name, address, phone);
	receiveInsertResponse();
}

void Client::sendInsertRequest(string name, string address, string phone){
	log.info("Sending insert request");
	requestsQ.send(createRequest(RequestEnum::INSERT));
	requestsQ.send(createInsertRequest(name, address, phone));
}

void Client::receiveInsertResponse(){
	log.info("Receiving insert response");

	insertResponse response;
	responsesQ.receive(this->sessionId, &response);

	if(response.result == INSERT_OK){
		printMessage("1 Record inserted");
	} else {
		printMessage("Error while inserting!");
	}
}

void Client::processRead(string input){

}

void Client::processSelect(string input){

}

void Client::processShutDown(string input){

}

struct request Client::createRequest(RequestEnum type){
	request req;
	req.mtype = static_cast<long>(RequestEnum::NEW_REQUEST);
	req.sessionId = this->sessionId;
	req.requestType = type;
	return req;
}

struct insertRequest Client::createInsertRequest(string name, string address, string phone){
	insertRequest req;
	req.mtype = this->sessionId;
	strcpy(req.nombre, name.c_str());
	strcpy(req.direccion, address.c_str());
	strcpy(req.telefono, phone.c_str());
	return req;
}

bool Client::openQueue(ClientQueue& queue){
	return queue.getQueue() == CONNECTION_OK;
}

bool Client::isClosed(){
	return closed;
}
