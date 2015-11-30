#include "client/Client.h"
#include <ArgumentHandler/ArgHandler.h>

using namespace std;

int main(int argc, char** argv) {

	ClientArgs args(argc, argv);

	std::string input;
	Client client;

	//Connect with DbManager
	if( client.connect() == CONNECTION_ERROR )
		exit(CONNECTION_ERROR);

	string file = args.getFile();
	if(!file.empty()){
		client.processFile(file);
		return 0;
	}


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
