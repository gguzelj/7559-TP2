#include <queue/ServerQueue.h>
#include <requests/DbRequest.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "manager/Manager.h"

using namespace std;

int main() {

	Manager manager;

	while(manager.isRunning()){
		manager.handleRequest();
	}

}
