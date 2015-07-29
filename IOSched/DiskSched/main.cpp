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
using namespace std;

int main(int argc, char* argv[])
{
	int caseType;
	char algo;
	char* operation;
	char comment;
	int timeStep;;
	int track;
	int ioId;
	string str;
	AbsSched* sched;;
	IoRequest* ioRequest;
	vector<IoRequest*> ioReqList;
	priority_queue<Event*, vector<Event*>, eventComparator> eventQueue;
	
	while((caseType = getopt(argc, argv, "s:")) != -1)
	{
		switch(caseType)
		{
			case 's' :
			algo =optarg[0];
			cout << "algo is " << algo << endl;
			break;
			 
		}
	}
	
	switch(algo)
	{
		case 'i':
		sched = new Fifo();
		break;
		
		default :
		sched = new Fifo();
		break;		
	}
	//cout << "optind" << argv[optind] << endl;
	fstream inFile(argv[optind], ios_base::in);
		
	while(getline(inFile, str))
	{
		
		if(str[0] != '#')
		{
			stringstream line(str);
			while(line  >> timeStep >> track)
			ioRequest =  new IoRequest(timeStep, track, ioId);
			ioReqList.push_back(ioRequest);;
			Event *event = new Event(ioId, timeStep, track, IoRequest::ADD);		
			eventQueue.push(event);
			ioId++;
		}
	}
	
	

	return 0;
}