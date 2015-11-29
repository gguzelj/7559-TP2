#ifndef DBREQUEST_H_
#define DBREQUEST_H_

#define NEW_REQUEST 1
#define INSERT 2
#define READ 3
#define SELECT 4

struct request {
	long mtype;
	long sessionId;
	long requestType;
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


#endif /* DBREQUEST_H_ */
