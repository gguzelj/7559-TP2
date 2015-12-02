#ifndef INSTRUCTIONHANDLER_H_
#define INSTRUCTIONHANDLER_H_

using namespace std;

class InstructionHandler {
public:

	InstructionHandler(long id) : sessionId(id){
	}

	RequestEnum getTypeRequest(string instr) {

		if (InstructionHandler::isInsert(instr))
			return RequestEnum::INSERT;

		if (InstructionHandler::isSelect(instr))
			return RequestEnum::SELECT;

		if (InstructionHandler::isShutDown(instr))
			return RequestEnum::SHUT_DOWN;

		return RequestEnum::UNKNOWN;
	}

	bool isExitInstruction(string instr){
		return isInstructionOf(instr,utils::IN_EXIT);
	}

	bool isInsert(string instr){
		return isInstructionOf(instr,utils::IN_INSERT);
	}

	bool isSelect(string instr){
		return isInstructionOf(instr,utils::IN_SELECT);
	}

	bool isShutDown(string instr){
		return isInstructionOf(instr,utils::IN_SHUT_DOWN);
	}

	bool isInstructionOf(string instr, string patter){
		string ins(instr);
		Helper::toLower(ins);
		if(ins.find(patter) != string::npos)
			return true;

		return false;
	}

	struct request createRequest(RequestEnum type){
		request req;
		req.mtype = static_cast<long>(RequestEnum::NEW_REQUEST);
		req.sessionId = this->sessionId;
		req.requestType = type;
		return req;
	}

	struct insertRequest createInsertRequest(string input){
		std::istringstream ss(input.substr(7));

		string name; getline(ss, name, ',');
		string address; getline(ss, address, ',');
		string phone; getline(ss, phone, ',');

		insertRequest req;
		req.mtype = this->sessionId;
		strcpy(req.nombre, name.c_str());
		strcpy(req.direccion, address.c_str());
		strcpy(req.telefono, phone.c_str());
		return req;
	}

	struct selectRequest createSelectRequest(string input){
		std::istringstream ss(input.substr(7));

		string name; getline(ss, name, ',');

		selectRequest req;
		req.mtype = this->sessionId;
		strcpy(req.nombre, name.c_str());
		return req;
	}

	struct shutDownRequest createShutDownRequest(){
		shutDownRequest req;
		req.mtype = this->sessionId;
		return req;
	}

private:
	long sessionId;


};

#endif /* INSTRUCTIONHANDLER_H_ */
