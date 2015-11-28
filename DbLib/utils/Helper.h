#ifndef UTILS_HELPER_H_
#define UTILS_HELPER_H_

#include <cstring>
#include <cerrno>
#include <string>
#include <sstream>
#include "../utils/utils.h"

class Helper {
public:

	static std::string errStr() {
	   char * e = strerror(errno);
	   return e ? e : "";
	}

	template<typename T>
	static std::string convertToString(T t){
		std::stringstream convert;
		convert << t;
		return std::string(convert.str());
	}

};

#endif /* UTILS_HELPER_H_ */
