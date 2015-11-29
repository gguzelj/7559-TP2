#include "Client.h"

Client::Client() :
		requestsQ(utils::QUEUE_FILE, utils::REQUESTS_QUEUE),
		responsesQ(utils::QUEUE_FILE, utils::RESPONSES_QUEUE),
		sessionId(getRandomUUID()),
		log(Logger::LogLevel::DEBUG) {
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

void Client::processInput(string input){

	if(input.find("INSERT") != string::npos)
		return processInsert(input);

	if(input.find("READ") != string::npos)
		return processRead(input);

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
	requestsQ.send(createRequest(INSERT));
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

struct request Client::createRequest(long type){
	request req;
	req.mtype = NEW_REQUEST;
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
