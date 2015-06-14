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
		FirstPass* fp = new FirstPass(myFile, fileSize);
		fp->doFirstPass(myFile, fileSize);
	
		//ReaderUtil* util = new ReaderUtil(myFile, fileSize);
		//cout << util->nextToken().getValue();
		
		return 0;
	}

	 
	
	
	
	
	
