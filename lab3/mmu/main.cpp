#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractAlgo.cpp"
#include "memMgmt.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	fstream myFile(argv[1], ios_base::in);
	int caseType;
    char caseValue;
	char comment;
	int pageVal; 
	string str;
	string algo;
	string option;
	int numFrames;
        
    while ((caseType = getopt(argc, argv, "a:o:f:")) != -1)
	{
		cout<< " inside getopt "<< endl;
             switch (caseType)
            {
				case 'a':
				algo = optarg;
				cout<< "algo " << algo << endl;
				break;
				case 'o':
				option = optarg;
				cout << " options " << option << endl; 
				break;
				case 'f':
				numFrames = atoi(optarg);
				cout << " frame number :  " << numFrames << endl; 
				break;
                
            }
	}	
	 fstream inputFile(argv[optind], ios_base::in);
     fstream randFile(argv[optind+1], ios_base::in);
	
	//fstream inputFile(argv[1], ios_base::in);
	while(inputFile >> comment)
	{
		if(comment == '#')
		{
			getline(inputFile, str);
			continue;
		}
		
		inputFile >> pageVal;
		cout << "the read write val " << comment << " page value " << pageVal << endl; 
		
	}
	
	return 0;

}
