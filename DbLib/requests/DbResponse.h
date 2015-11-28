#ifndef DBRESPONSE_H_
#define DBRESPONSE_H_

#define CONNECTION_RESPONSE 0
#define INSERT_RESPONSE 1
#define READ_RESPONSE 2
#define SELECT_RESPONSE 3

typedef struct {
	long mtype = CONNECTION_RESPONSE;
	unsigned int result;
	long connectionId;
} connectionResponse;

typedef struct {
	long mtype = INSERT_RESPONSE;
	unsigned int result;
} insertResponse;

typedef struct {
	long mtype = READ_RESPONSE;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} readResponse;

typedef struct {
	long mtype = SELECT_RESPONSE;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} selectResponse;


#endif /* DBRESPONSE_H_ */
