// linker.cpp : Defines the entry point for the console application.
//


#include <fstream>
#include <string>
#include "Token.h"
#include "SingleModule.cpp"
#include "FirstPass.cpp"


using namespace std;

	
	int main(int argc, char* argv[])
	{
		long fileSize;
		SymbolList* sl = new SymbolList();
		if (argc != 2)
		{
			cout << "Number of arguments is not two " << endl;
			return 0;
		}

		fstream* myFile = new fstream(argv[1], fstream::in| ios::ate);
		fileSize = myFile->tellg();
		myFile->seekg(0);
		myFile->unsetf(ios_base::skipws);
		if (!myFile->good()) 
		{
			cout << "file is not good" << endl;
			return 0;
		}
		FirstPass* fp = new FirstPass(myFile, fileSize, sl);
		fp->doFirstPass();
		
		sl->printList();
		//ReaderUtil* util = new ReaderUtil(myFile, fileSize);
		
		delete fp;
		myFile->close();
		myFile = new fstream(argv[1], fstream::in);
		myFile->unsetf(ios_base::skipws);
		
		//fileSize = myFile->tellg();
		FirstPass* sp = new FirstPass(myFile, fileSize, sl);	
		sp->doSecondPass();
		sl->isDef();
		return 0;
	}
	

	 
	
	
	
	
	
