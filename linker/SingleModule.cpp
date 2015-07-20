#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Token.h"
#include "ReaderUtil.cpp"
#include "SymbolList.cpp"

using namespace std;

class SingleModule {

	private:
	fstream* fin;
	long fileSize;
	int count;
	char ch;
	ReaderUtil* util;
	
		
	public:
	SingleModule(fstream* in, long fSize)
	{
		this->fin = in;
		this->fileSize = fSize;
		util = new ReaderUtil(fin, fileSize);
		
		
	}
	 
	void* readDefList(int modCount, int baseAddr, SymbolList* sl )
	{
		Token<int> newInteger = util->getInteger(true);
	
		//cout << "reading def list" << endl;
		int count = newInteger.getValue(); 
		//cout << "Count is " << count << endl;
		if (count > 16)
		{
			cout << "Parse Error line " << newInteger.getLineNumber() << " offset " << newInteger.getColumnNumber() << ": TO_MANY_DEF_IN_MODULE " << endl ;
			exit(99);
		}
		//cout << "Count after if condition is " << count << endl;
		while(count--)
		{
			//cout << "about to read the symbol" << endl;			
			Symbol sym = util->getSymbol();
			sym.setModCount(modCount);
			sym.setModAddr(baseAddr);
			//sym.setAbsAddr(baseAddr+);
			//cout << " read the integer " << endl;
			Token<int> tok = util->getInteger(false);
			sym.setRelAddr(tok.getValue());
			sym.setAbsAddr(baseAddr + tok.getValue());
			sl->pushList(sym);
			
		}
		
	}
	
	void readUseList()
	{
		Token<int> newInteger = util->getInteger(false);
		//cout << "reading use list" << endl;
		int count = newInteger.getValue(); 
		
		if (count > 16)
		{
			cout << "Parse Error line " << newInteger.getLineNumber() << " offset " << newInteger.getColumnNumber() << ": TO_MANY_USE_IN_MODULE " << endl ;
			exit(99);
		}
		
		while(count--)
		{
			Symbol sym = util->getSymbol();
			
		}
		
	}
	
	int readProgramText(int modCount)
	{
		Token<int> newInteger = util->getInteger(false);
		//cout << "reading program text " << endl;
		int count = newInteger.getValue(); 
		if((count + modCount) > 512)
		{
			cout << "Parse Error line " << newInteger.getLineNumber() << " offset " << newInteger.getColumnNumber() << ": TO_MANY_INSTR " << endl ;
			exit(99);
		}			
		//cout << " base addr1 " << baseAddr;
		int progCount = count;
		while(count--)
		{
			util->getAddr();
			util->getInteger(false);
		}
	return progCount;
	//cout << " the base addres of module " << modCount << " is " << baseAddr << endl;  
	
	}
	
	
};
