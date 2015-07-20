#ifndef SCHEDULER_CPP
#define SCHEDULER_CPP
//////////////////////////////////////
#include "Process.cpp"
#include <queue>


using namespace std;

class Scheduler
{
	protected:
	
	int quantum;
	public:
	virtual void addProcess(Process*) = 0;
	virtual Process* getNextProcess(void) = 0;
	virtual int getQuantum(void) = 0;
};

#endif