#include <string>

using namespace std;

class Instruction 
{
	private 
	char opCode;
	int operand;
	
	public:
	Instruction(char opCode, int operand)
	{
		this->opCode = opCode;
		this->operand = operand;
	}
	
	void setOpCode(char opCode)
	{
		this->opCode = opCode;
	}
	char getOpCode()
	{
		return this->opCode;
	}
	
	
	void setOperand(int operand)
	{
		this->operand = operand;
	}
	char getOperand()
	{
		return this->operand;
	}
};
