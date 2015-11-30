#ifndef DBRESPONSE_H_
#define DBRESPONSE_H_

#define CONNECTION_RESPONSE 0
#define INSERT_RESPONSE 1
#define READ_RESPONSE 2
#define SELECT_RESPONSE 3

#define INSERT_OK 1
#define INSERT_ERROR 2

#define CONNECTION_OK 0
#define CONNECTION_ERROR 1

struct newConnectionResponse{
	long mtype;
	unsigned int result;
	long connectionId;
};

struct insertResponse{
	long mtype;
	unsigned int result;
};

struct readResponse{
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
};

struct selectResponse{
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
};

struct shutDownResponse{
	long mtype;
	bool success;
};

#endif /* DBRESPONSE_H_ */
