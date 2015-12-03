#ifndef DBREQUEST_H_
#define DBREQUEST_H_

enum class RequestEnum
	: int {
		NEW_REQUEST = 1, INSERT = 2, SELECT = 3, SHUT_DOWN = 4, HELP = 5, EXIT = 6, UNKNOWN = 7
};

struct request {
	long mtype;
	long sessionId;
	RequestEnum requestType;
};

struct insertRequest{
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
};

struct selectRequest{
	long mtype;
	char nombre[61];
};

struct shutDownRequest{
	long mtype;
	long sessionId;
};


#endif /* DBREQUEST_H_ */
