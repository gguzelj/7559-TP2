#ifndef DBREQUEST_H_
#define DBREQUEST_H_

#define CONNECTION_REQUEST 0
#define INSERT_REQUEST 1
#define READ_REQUEST 2
#define SELECT_REQUEST 3

#define CONNECTION_OK 0
#define CONNECTION_ERROR 1

#define INSERT_OK 0;
#define INSERT_ERROR 1;

typedef struct {
	long mtype = CONNECTION_REQUEST;
	long clientUUID;
} connectionRequest;

typedef struct {
	long mtype = INSERT_REQUEST;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} insertRequest;

typedef struct {
	long mtype = READ_REQUEST;
	unsigned int line;
} readRequest;

typedef struct {
	long mtype = SELECT_REQUEST;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} selectRequest;


#endif /* DBREQUEST_H_ */
