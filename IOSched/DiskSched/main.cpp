#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "IoRequest.cpp"
#include "Event.cpp"
#include "Transition.cpp"
#include "AbsSched.cpp"
#include "Schedulers.cpp"
#include "Sstf.cpp"
#include "Elevator.cpp"
#include "Cscan.cpp"
#include "Fscan.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	int caseType = 0;
	char algo;
	char* operation;
	char comment;
	int timeStep = 0;;
	int track= 0;
	int ioId= 0;
	string str;
	bool vflag;
	AbsSched* sched;;
	IoRequest* ioRequest;
	vector<IoRequest*> ioReqList;
	priority_queue<Event*, vector<Event*>, eventComparator> eventQueue;

	while((caseType = getopt(argc, argv, "vs:")) != -1)
	{
		switch(caseType)
		{
			case 's': 
				algo =optarg[0];
				break;

			case 'v':
				vflag = true;
				break;
		}
	}

	switch(algo)
	{
		case 'i':
			sched = new Fifo();
			break;

		case 'j':
			sched = new Sstf();
			break;

		case 's':
			sched = new Elevator();
			break;

		case 'c':
			sched = new Cscan();
			break;

		case 'f':
			sched = new FSCAN();
			break;

	}

	fstream inFile(argv[optind], ios_base::in);

	while(getline(inFile, str))
	{

		if(str[0] != '#')
		{
			stringstream line(str);
			while(line  >> timeStep >> track){
				ioRequest =  new IoRequest(timeStep, track, ioId);
			}
			ioReqList.push_back(ioRequest);;
			Event *event = new Event(ioId, timeStep, track, IoRequest::ADD);		
			eventQueue.push(event);
			ioId++;
		}
	}

	Transition* trans = new Transition(eventQueue, ioReqList, sched, vflag);
	trans->transLogic();
	trans->ioReqsInfo();
	trans->printSummary();


	return 0;
}
