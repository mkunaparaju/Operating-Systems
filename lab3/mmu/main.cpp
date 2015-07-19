#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractAlgo.cpp"
#include "memMgmt.cpp"
#include "FIFO.cpp"
#include "RandNum.cpp"
#include "PrAlgos.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	fstream myFile(argv[1], ios_base::in);
	int caseType;
	char caseValue;
	char operation;
	int pageVal; 
	string str;
	char algo;
	string option;
	int numFrames;
	vector<unsigned int>* frameTable;
	vector<unsigned int>* ftop;
	vector<Pte*>* pageTable = new vector<Pte*>(64);
	for(int i = 0; i < 64; i++){
		pageTable->at(i) = new Pte();
	}
	AbstractAlgo* prAlgo;

	while ((caseType = getopt(argc, argv, "a:o:f:")) != -1)
	{
		//cout<< " inside getopt "<< endl;
		switch (caseType)
		{
			case 'a':
				algo = optarg[0];
				//cout<< "algo " << algo << endl;
				break;
			case 'o':
				option = optarg;
				//cout << " options " << option << endl; 
				break;
			case 'f':
				numFrames = atoi(optarg);
				//cout << " frame number :  " << numFrames << endl; 
				break;

		}
	}	

	frameTable = new vector<unsigned int>();
	ftop = new vector<unsigned int>(numFrames);

	for(int i = 0; i < numFrames; i++)
	{
		ftop->at(i) = -1;
	}
	RandNum* rn = new RandNum(argv[optind+1]);
	switch (algo)
	{
		case 'f':
			prAlgo = new Fifo(pageTable, frameTable ,ftop);
			break;
		case 'r':
			prAlgo = new Random(pageTable, frameTable ,ftop, rn);
			break;
		case 's':
			//cout << "inseconnd chance" << endl;
			prAlgo = new SecondChance(pageTable, frameTable ,ftop);
			break;
			case 'c':
			//cout << "inseconnd chance" << endl;
			prAlgo = new Clock(pageTable, frameTable ,ftop);
			break;

	}

	//cout << "about to read input file" << endl;
	fstream inputFile(argv[optind], ios_base::in);


	MemMgmt* mmu = new MemMgmt(pageTable, frameTable, ftop, prAlgo,numFrames);
	string::iterator si1;;
	for(si1 = option.begin() ; si1 < option.end(); si1++)
	{
		switch(*si1)
		{
			case 'O':
				mmu->setDetailPrint(true);
				break;
			case 'P':
				mmu->setPtePrint(true);
				break;
			case 'F':
				mmu->setFtePrint(true);
				break;
			case 'S':
				mmu->setSumPrint(true);
				break;

		}
	}

//	cout << "set alkl options in mmu" << endl;

	//fstream inputFile(argv[1], ios_base::in);
	while(inputFile >> operation)
	{
		if(operation == '#')
		{
			getline(inputFile, str);
			//cout << "saw a commennt " << endl;
			continue;
		}

		inputFile >> pageVal;
		//cout << "the read write val " << operation << " page value " << pageVal << endl; 
		mmu->instrHandle(operation, pageVal);
	} 
	//cout << "exiting the while loop" << endl;
	mmu->pageTablePrint();
	mmu->frameTablePrint();
	mmu->summaryPrint();

	return 0;

}
