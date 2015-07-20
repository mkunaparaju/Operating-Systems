#ifndef RANDNUM
#define RANDNUM

#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
using namespace std;

class RandNum
{
private:
	string randLine;
	long long randValue;
	fstream randFile;

public:

	RandNum	(char* rFile)
	{
		randFile.open(rFile, ios_base::in);
		getline(randFile, randLine);
	}

	int getRandNum()
	{
	getline(randFile, randLine);
		if (randFile.eof())
		{
			randFile.clear();
			randFile.seekg(0, ios::beg);
			getline(randFile, randLine);
			getline(randFile, randLine);
		}
		
		//cout << "read " << randLine << endl;
		istringstream iss(randLine);
		if (!(iss >> randValue))
		{
			//cout << "exiting from program " << endl;
			exit(99);
		}

		return randValue;

	}

};
#endif
