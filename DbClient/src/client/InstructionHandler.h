#ifndef INSTRUCTIONHANDLER_H_
#define INSTRUCTIONHANDLER_H_

using namespace std;

class InstructionHandler {
public:

	static RequestEnum getType(string instr) {

		if (InstructionHandler::isInsert(instr))
			return RequestEnum::INSERT;

		if (InstructionHandler::isRead(instr))
			return RequestEnum::READ;

		if (InstructionHandler::isSelect(instr))
			return RequestEnum::SELECT;

		if (InstructionHandler::isShutDown(instr))
			return RequestEnum::SHUT_DOWN;

		return RequestEnum::UNKNOWN;
	}

	static bool isInsert(string instr){
		string ins(instr);
		Helper::toLower(ins);
		if(ins.find(utils::IN_INSERT) != string::npos)
			return true;

		return false;
	}

	static bool isRead(string instr){
		string ins(instr);
		Helper::toLower(instr);
		if(ins.find(utils::IN_READ) != string::npos)
			return true;

		return false;
	}

	static bool isSelect(string instr){
		string ins(instr);
		Helper::toLower(instr);
		if(ins.find(utils::IN_SELECT) != string::npos)
			return true;

		return false;
	}

	static bool isShutDown(string instr){
		string ins(instr);
		Helper::toLower(instr);
		if(ins.find(utils::IN_SHUT_DOWN) != string::npos)
			return true;

		return false;
	}

};

#endif /* INSTRUCTIONHANDLER_H_ */
