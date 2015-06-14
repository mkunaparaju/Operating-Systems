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
	int cou
	nt;
	char ch;
	ReaderUtil* util;
	SymbolList* sl;
	
	

	
	public:
	SingleModule(fstream* in, long fSize)
	{
		this->fin = in;
		this->fileSize = fSize;
		util = new ReaderUtil(fin, fileSize);
		sl = new SymbolList();
	}
	 
	void readDefList(int modCount, int baseAddr )
	{
		Token<int> newInteger = util->getInteger(true);
	
		//cout << "reading def list" << endl;
		int count = newInteger.getValue(); 
		//cout << "Count is " << count << endl;
		if (count > 16)
		{
			cout << "Parse error line " << newInteger.getLineNumber() << " offset " << newInteger.getColumnNumber() << " TO_MANY_DEF_IN_MODULE " << endl ;
			exit(99);
		}
		//cout << "Count after if condition is " << count << endl;
		while(count--)
		{
			//cout << "about to read the symbol" << endl;			
			Symbol sym = util->getSymbol();
			sym.setModCount(modCount);
			sym.setModAddr(baseAddr);
			sym.setRelAddr(baseAddr+)
			
			sl->pushList(sym);
			//cout << " read the integer " << endl;
			util->getInteger(false);
		}
	}
	
	void readUseList()
	{
		Token<int> newInteger = util->getInteger(true);
		//cout << "reading use list" << endl;
		int count = newInteger.getValue(); 
		
		if (count > 16)
		{
			cout << "Parse error line " << newInteger.getLineNumber() << " offset " << newInteger.getColumnNumber() << " TO_MANY_USE_IN_MODULE " << endl ;
			exit(99);
		}
		
		while(count--)
		{
			util->getSymbol();
		}
	}
	
	int readProgramText()
	{
		Token<int> newInteger = util->getInteger(true);
		//cout << "reading program text " << endl;
		int count = newInteger.getValue(); 
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
