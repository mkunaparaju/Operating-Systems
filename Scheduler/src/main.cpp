#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Transition.cpp"
#include "Fifo.cpp"
#include "RoundRobin.cpp"
#include "Lcfs.cpp"
#include "Sjf.cpp"
#include "Prio.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	int arrTime;
	int cpuTime;
	int cpuBurst;
	int ioBurst;
	int pid = 0;
	int prio;
	int sFlag;
	bool vFlag = false;
	int caseType;
	int quantum;
	char casevalue;
	string randLine;
	char* schedName = new char[16];
	Scheduler *sched;
	char numstr[21]; 
	vector<Process*> processList;
	priority_queue<Event*, vector<Event*>, eventComparator> eventQueue;

	////////////////////////////////////
	//getting verbose scheduler inputs//
	////////////////////////////////////

	while ((caseType = getopt(argc, argv, "vs:")) != -1)
	{
		switch (caseType)
		{
			case 's':
				sFlag = 1;
				casevalue = optarg[0];
				if (casevalue == 'R' || casevalue == 'P' )
				{
					sscanf(optarg+1, "%d", &quantum);
				}
				else 
				{
					quantum = 9999;
				}
				break;

			case 'v':
				vFlag = true;
				break;

		}
	}

	fstream myFile(argv[optind], ios_base::in);
	RandNum* rn = new RandNum(argv[optind+1]);

	switch (casevalue)
	{
		case 'F':

			sched = new Fifo(quantum);
			schedName = (char*)"FCFS";
			break;
		case 'S':
			sched = new Sjf(quantum);
			schedName = (char*)"SJF";
			break;
		case 'R':
			sprintf(schedName, "RR %d", quantum);
			sched = new RoundRobin(quantum);
			break;
		case 'P':
			sprintf(schedName, "PRIO %d", quantum);
			sched = new Prio(quantum);
			break;
		case 'L':
			sched = new Lcfs(quantum);
			schedName = (char*)"LCFS";
			break;
		default:
			cout<< "Unknown Scheduler"<< endl;
			exit(99);
	}

	while (myFile >> arrTime >> cpuTime >> cpuBurst >> ioBurst)
	{
		int num = rn->getRandNum();
		prio = 1+ (num%4);
		Process *process = new Process(arrTime, cpuTime, cpuBurst, ioBurst, pid, prio);
		processList.push_back(process);
		pid++;
	}

	for (int i = 0; i < processList.size(); i++)
	{
		Event *event = new Event(processList[i]->getPid(), processList[i]->getArrTime(), Process::CREATED, Process::READY);
		eventQueue.push(event);
	}

	Transition* trans = new Transition(eventQueue,processList, rn, sched,vFlag);
	trans->transLogic();
	trans->summary(schedName);
	trans->finalSummary();
	return 0;
}
