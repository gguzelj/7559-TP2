#ifndef ARGHANDLER_H_
#define ARGHANDLER_H_

#include <string>

#include "../tclap/CmdLine.h"
#include "../tclap/ValueArg.h"

class ClientArgs {
public:

	ClientArgs(int argc, char** argv) :
			cmd("DbClient", ' ', "0.0.1"),
			file("f", "file", "File Name", false, "", "string"){
		cmd.add(file);
		cmd.parse(argc, argv);
	}

	~ClientArgs(){
	}

	std::string getFile(){
		return file.getValue();
	}


private:
	TCLAP::CmdLine cmd;
	TCLAP::ValueArg<std::string> file;

};

#endif /* ARGHANDLER_H_ */
