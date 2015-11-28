#include "Manager.h"

Manager::Manager() : queue(utils::QUEUE_FILE, utils::QUEUE_FILE_CHAR), log(utils::LOG_FILE) {
	log.debug("Creating DbManager");
	log.debug("Creating DbManager Queue");
	queue.create();
	log.debug("DbManager Queue created");
}

Manager::~Manager() {

}

