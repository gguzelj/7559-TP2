#include "client/Client.h"
#include <ArgumentHandler/ArgHandler.h>
#include <utils/Helper.h>

using namespace std;

int main(int argc, char** argv) {

	ClientArgs args(argc, argv);

	std::string input;
	Client client;

	//Connect with DbManager
	if( client.connect() == CONNECTION_ERROR )
		exit(CONNECTION_ERROR);

	//File processing
	if(args.isFileSet()){
		client.processFile(args.getFile());
		return 0;
	}

	//Online client
	while(!client.isClosed()){
		client.processInput(cin);
	}

}
