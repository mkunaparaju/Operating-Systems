#ifndef EVENT_CPP
#define EVENT_CPP
///////////////////////////////////////////
#include "Process.cpp"
using namespace std;

class Event
{
private:
	int pid;
	int timeStamp;
	static int eid;
	int e_counter;
	Process::states prevState;
	Process::states newState;

public:
	Event(int pid, int tStamp, Process::states prevState, Process::states newState)
	{
		this->pid = pid;
		this->timeStamp = tStamp;
		this->prevState = prevState;
		this->newState = newState;
		this->e_counter = eid++;
	}

	void setTimeStamp(int tStamp)
	{
		timeStamp = tStamp;
	}
	int getTimeStamp()
	{
		return this->timeStamp;
	}
	int getPid()
	{
		return pid;
	}

	int getEid()
	{
		return e_counter;
	}

	Process::states getPrevState()
	{
		return prevState;
	}
	void setPrevState(Process::states prevState)
	{
		this->prevState = prevState;
	}
	Process::states getNewState()
	{
		return newState;
	}
	void setNewState(Process::states newState)
	{
		this->newState = newState;
	}
};

int Event::eid = 0;
#endif
