#ifndef DBREQUEST_H_
#define DBREQUEST_H_

enum class RequestEnum
	: int {
		NEW_REQUEST = 1, INSERT = 2, READ = 3, SELECT = 4, SHUT_DOWN = 5, UNKNOWN = 6
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

struct readRequest{
	long mtype;
	unsigned int line;
};

struct selectRequest{
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
};

struct shutDownRequest{
	long mtype;
	long sessionId;
};


#endif /* DBREQUEST_H_ */
