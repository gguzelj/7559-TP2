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

	static void printClientMsg(){
		std::cout << "Client> ";
	}

	static void printUsage(){
		std::cout << "client Usage: available commands:" << std::endl;
		std::cout << "SELECT: 'select nombre,direccion,telefono'" << std::endl;
		std::cout << "INSERT: 'insert nombre,direccion,telefono'" << std::endl;
		std::cout << "EXIT: 'exit' -> quit" << std::endl;
	}

	static void printManagerMsg(std::string msg){
		std::cout << "Manager> " << msg << std::endl;
	}

	static long getRandomUUID(){
		srand (time(NULL));
		return static_cast<long>(rand());
	}

};

#endif /* UTILS_HELPER_H_ */
