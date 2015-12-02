#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace utils {

static const std::string IN_EXIT = "exit";
static const std::string IN_INSERT = "insert";
static const std::string IN_SELECT = "select";
static const std::string IN_SHUT_DOWN = "shut_down";

static const std::string QUEUE_FILE = "../../README.md";
static const char REQUESTS_QUEUE = '1';
static const char RESPONSES_QUEUE = '2';

static const std::string LOG_DELIMITER = " - ";
static const std::string LOG_FILE = "/tmp/TPConcurrentes.log";

}

#endif
