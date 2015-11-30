#ifndef UTILS_HELPER_H_
#define UTILS_HELPER_H_

#include <iostream>
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

	static void toLower(std::string &str) {
		for (unsigned int i = 0; i < str.length(); ++i)
			str[i] = tolower(str[i]);
	}

	static void printClientMsg(std::string msg){
		std::cout << "Client> " << msg << std::endl;
	}

};

#endif /* UTILS_HELPER_H_ */
