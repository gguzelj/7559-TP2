#include "Manager.h"

Manager::Manager() :
		requestsQ(utils::QUEUE_FILE, utils::REQUESTS_QUEUE),
		responsesQ(utils::QUEUE_FILE, utils::RESPONSES_QUEUE),
		running(true){

	requestsQ.create();
	responsesQ.create();
	Helper::printManagerMsg("All Queues created");
}

Manager::~Manager() {
	requestsQ.destroy();
	responsesQ.destroy();
	Helper::printManagerMsg("All Queues deleted");
}

void Manager::handleRequest(){
	request request;
	requestsQ.receive(static_cast<long>(RequestEnum::NEW_REQUEST), &request);

	switch (request.requestType) {
		case RequestEnum::INSERT:
			return handleInsertRequest(request);
		case RequestEnum::READ:
			return handleReadRequest(request);
		case RequestEnum::SELECT:
			return handleSelectRequest(request);
		case RequestEnum::SHUT_DOWN:
			return handleShutDownRequest(request);
		default:
			Helper::printManagerMsg("Unknown type of request received!");
	}

}

void Manager::handleInsertRequest(const request request){

	insertRequest insertRequest;
	requestsQ.receive(request.sessionId, &insertRequest);

	std::string msg("Inserting new record with ");
	msg.append("name: ").append(insertRequest.nombre);
	msg.append(", address: ").append(insertRequest.direccion);
	msg.append(", phone: ").append(insertRequest.telefono);
	Helper::printManagerMsg(msg);

	//LOGICA PARA INSERTAR REGISTRO!!

	insertResponse response;
	response.mtype = request.sessionId;
	response.result = INSERT_OK;
	responsesQ.send(response);
}

void Manager::handleReadRequest(const request readRequest){
}

void Manager::handleSelectRequest(const request selectRequest){
}

void Manager::handleShutDownRequest(const request request){
	shutDownRequest shutDownRequest;
	requestsQ.receive(request.sessionId, &shutDownRequest);

	std::string msg("Shutting down request from client ");
	msg.append(Helper::convertToString(request.sessionId));
	Helper::printManagerMsg(msg);

	running = false;

	shutDownResponse response;
	response.mtype = request.sessionId;
	response.success = true;

	responsesQ.send(response);
}

bool Manager::isRunning(){
	return running;
}
