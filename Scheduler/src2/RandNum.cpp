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
	int randValue;
	fstream randFile;

public:

	RandNum	(char* rFile)
	{
		randFile.open(rFile, ios_base::in);
		getline(randFile, randLine);
	}

	int getRandNum()
	{

		if (randFile.eof())
		{
			randFile.seekg(0, ios::beg);
			getline(randFile, randLine);
		}
		getline(randFile, randLine);
		istringstream iss(randLine);
		if (!(iss >> randValue))
		{
			exit(99);
		}

		return randValue;

	}

};
#endif