#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace utils {

static const std::string QUEUE_FILE = "../../README.md";
static const char REQUEST_QUEUE = '1';
static const char CONNECTION_QUEUE = '2';
static const char INSERT_QUEUE = '3';
static const char READ_QUEUE = '4';
static const char SELECT_QUEUE = '5';

static const std::string LOG_DELIMITER = " - ";
static const std::string LOG_FILE = "/tmp/TPConcurrentes.log";

}

#endif
