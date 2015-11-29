#include "client/Client.h"

using namespace std;

int main() {

	std::string input;
	Client client;

	//Connect with DbManager
	if( client.connect() == CONNECTION_ERROR )
		exit(CONNECTION_ERROR);

	//Process requests
	while(true){
		getline(cin, input);
		if(string("exit").compare(input) == 0){
			cout << "C ya!" << endl;
			break;
		}
		client.processInput(input);
	}

}
