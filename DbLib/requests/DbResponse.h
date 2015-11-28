#ifndef DBRESPONSE_H_
#define DBRESPONSE_H_

#define CONNECTION_RESPONSE 0
#define INSERT_RESPONSE 1
#define READ_RESPONSE 2
#define SELECT_RESPONSE 3

#define CONNECTION_OK 0
#define CONNECTION_ERROR 1

typedef struct {
	long mtype;
	unsigned int result;
	long connectionId;
} newConnectionResponse;

typedef struct {
	long mtype;
	unsigned int result;
} insertResponse;

typedef struct {
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} readResponse;

typedef struct {
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} selectResponse;


#endif /* DBRESPONSE_H_ */
