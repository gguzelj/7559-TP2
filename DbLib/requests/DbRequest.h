#ifndef DBREQUEST_H_
#define DBREQUEST_H_

#define NEW_CONNECTION 1
#define INSERT 2
#define READ 3
#define SELECT 4

typedef struct {
	long mtype = 0;
	long typeRequest;
	long connectionId;
} request;

typedef struct {
	long mtype;
	long clientUUID;
} newConnectionRequest;

typedef struct {
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} insertRequest;

typedef struct {
	long mtype;
	unsigned int line;
} readRequest;

typedef struct {
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} selectRequest;


#endif /* DBREQUEST_H_ */
