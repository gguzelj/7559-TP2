#include "Manager.h"

Manager::Manager() :
		entities("people.dat"),
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

	Entity ent;

	strncpy(ent.nombre, insertRequest.nombre, sizeof(insertRequest.nombre));
	ent.nombre[sizeof(insertRequest.nombre) - 1] = '\0';

	strncpy(ent.direccion, insertRequest.direccion, sizeof(insertRequest.direccion));
	ent.direccion[sizeof(insertRequest.direccion) - 1] = '\0';

	strncpy(ent.telefono, insertRequest.telefono, sizeof(insertRequest.telefono));
	ent.telefono[sizeof(insertRequest.telefono) - 1] = '\0';

	entities.persist(ent);

	insertResponse response;
	response.mtype = request.sessionId;
	response.result = INSERT_OK;
	responsesQ.send(response);
}

void Manager::handleSelectRequest(const request request){
	Entity ent;
	selectRequest selectRequest;
	requestsQ.receive(request.sessionId, &selectRequest);

	std::string msg("Executing select request from client ");
	msg.append(Helper::convertToString(request.sessionId));
	Helper::printManagerMsg(msg);

	std::list<Entity> result;
	entities.findAll(selectRequest.nombre, result);

	selectResultsResponse resultsResponse;
	resultsResponse.mtype = request.sessionId;
	resultsResponse.matches = result.size();
	responsesQ.send(resultsResponse);

	selectResponse selectResponse;
	selectResponse.mtype = request.sessionId;

	for (std::list<Entity>::iterator it = result.begin(); it != result.end(); it++){
		ent = *it;
		strcpy(selectResponse.nombre, ent.nombre);
		strcpy(selectResponse.direccion, ent.direccion);
		strcpy(selectResponse.telefono, ent.telefono);
		responsesQ.send(selectResponse);
	}

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
