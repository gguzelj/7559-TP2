#include <queue/ServerQueue.h>
#include <requests/DbRequest.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "manager/Manager.h"

using namespace std;

int main() {

	Manager manager;

	cout << "creando cola" << endl;

	ServerQueue cola(std::string("/Recept.log"), '1');
	cola.create();

	cout << "cola creada" << endl;

	insertRequest request;

	cout << "recibiendo erquest" << endl;

	cola.receive(INSERT_REQUEST, &request);

	cout << "request envciada... telefono: "<< request.telefono << endl;

	sleep(10);
}
