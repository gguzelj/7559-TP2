#include "Manager.h"

Manager::Manager() :
		requestsQ(utils::QUEUE_FILE, utils::REQUESTS_QUEUE),
		responsesQ(utils::QUEUE_FILE, utils::RESPONSES_QUEUE),
		log(Logger::LogLevel::DEBUG, "DB_MANAGER") {

	log.debug("Creating DbManager");

	log.debug("Creating requests Queue");
	requestsQ.create();

	log.debug("Creating responses Queue");
	responsesQ.create();

	log.debug("All queues created");
	log.debug("DbManager created");
}

Manager::~Manager() {
	log.debug("Deleting DbManager");

	log.debug("Deleting requests Queue");
	requestsQ.destroy();

	log.debug("Deleting responses Queue");
	responsesQ.destroy();

	log.debug("All queues Deleted");
	log.debug("DbManager Deleted");
}

void Manager::handleRequest(){
	log.debug("Waiting for requests");

	request request;
	requestsQ.receive(static_cast<long>(RequestEnum::NEW_REQUEST), &request);

	log.info("New request from {}", request.sessionId);

	switch (request.requestType) {
		case RequestEnum::INSERT:
			return handleInsertRequest(request);
		case RequestEnum::READ:
			return handleReadRequest(request);
		case RequestEnum::SELECT:
			return handleSelectRequest(request);
		default:
			log.error("Unknown type of request");
	}

}

void Manager::handleInsertRequest(const request request){
	log.info("Reading insert request from CLIENT-{}", request.sessionId);

	insertRequest insertRequest;
	requestsQ.receive(request.sessionId, &insertRequest);

	log.info("InsertRequest received");
	log.info("Insert new record with name {}, address {}, phone {}",
			insertRequest.nombre, insertRequest.direccion, insertRequest.telefono);

	insertResponse response;
	response.mtype = request.sessionId;
	response.result = INSERT_OK;

	responsesQ.send(response);
}

void Manager::handleReadRequest(const request readRequest){
	log.info("READ REQUEST!! no handler yet..");
}

void Manager::handleSelectRequest(const request selectRequest){
	log.info("SELECT REQUEST!! no handler yet..");
}
