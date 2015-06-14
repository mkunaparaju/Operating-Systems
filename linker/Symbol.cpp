#include <string>
#include "Token.h"

using namespace std;

class Symbol 
{
private:
	int lineNumber;
	int columnNumber;
	bool isMultDef;
	bool isUsed;
	string token;
	int modCount;
	int modAddr;
	int relAddr;

public:
	 
	Symbol (Token<char*> tok)
	{
		this->lineNumber = tok.getLineNumber();
		this->columnNumber = tok.getColumnNumber();
		this->token = tok.getValue();
	}
	



	void setMultDef(bool multDefined)
	{
		isMultDef = multDefined;;
	}

	bool getMultDef()
	{
		return isMultDef;
	}

	void setUsed(bool used)
	{
		isUsed = used;
	}
	bool getIsUsed()
	{
		return isUsed;
	}
	void setModCount(int modCount)
	{
		this->modCount = modCount;
	}

	int getModCount()
	{
		return modCount;
	}
	
	void setModAddr(int modAddr)
	{
		this->modAddr = modAddr;
	}

	int getModAddr()
	{
		return modAddr;
	}


	void setRelAddr(int relAddr)
	{
		this->relAddr = relAddr;
	}

	int getRelAddr()
	{
		return relAddr;
	}
	
		string getToken( )
	{
		return token;
	}

};
