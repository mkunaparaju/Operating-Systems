#ifndef DISKSCHED_CPP
#define DISKSCHED_CPP

#include <queue>
#include "Event.cpp"
#include "AbsSched.cpp"
#include "IoRequest.cpp"

using namespace std;

struct eventComparator
{
	bool operator()(Event* lhs, Event* rhs) const
	{
			return lhs->getTimeStep() > rhs->getTimeStep();

	}
};

class Transition	
{
	private:
	
	priority_queue<Event*, vector<Event*>, eventComparator> eventQueue;
	vector<IoRequest*> ioReqList;
	AbsSched* sched;
	
	public:
	Transition(priority_queue<Event*, vector<Event*>, eventComparator> eventQueue, vector<IoRequest*> ioReqList, AbsSched* sched  )
	{
		this->eventQueue = eventQueue;
		this->ioReqList = ioReqList;
		this->sched = sched;
	}
	
	void transLogic()
	{
		cout<< "in transition" << endl;
	}
	
};
#endif