#ifndef DISKSCHED_CPP
#define DISKSCHED_CPP

#include <queue>
#include <iomanip>
#include "Event.cpp"
#include "AbsSched.cpp"
#include "IoRequest.cpp"

using namespace std;

struct eventComparator
{
	bool operator()(Event* lhs, Event* rhs) const
	{
		if(lhs->getTimeStep() == rhs->getTimeStep())
		{
			return lhs->getEid() > rhs->getEid();;
		}
			
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
		cout << "TRACE" << endl;
		int curTimeStep =0;
		int curEventTrack =0;
		int curTrack=0;;
		int reqID;
		int nextIoFreeTime =0;
		int trackMove =0;;	
		
		while(eventQueue.size() >0)
		{
			Event* event = eventQueue.top();
			eventQueue.pop();
			curTimeStep = event->getTimeStep();
			reqID = event->getIoId();
			curEventTrack = event->getTrack();
			IoRequest* currIoReq = ioReqList[reqID];
			
			if(event->getState() == IoRequest::ADD)
			{

				sched->addRequest(currIoReq);
				cout << curTimeStep << ":" << setw(6) << setfill(' ') << reqID << " add " << curEventTrack << endl;
       
			}
			else if(event->getState() == IoRequest::ISSUE)
			{
				currIoReq->setIssueTime(curTimeStep);
				trackMove = abs(curEventTrack - curTrack);
				Event* newEvent  = new Event(currIoReq->getIoId(), curTimeStep+trackMove, curEventTrack, IoRequest::FINISH);
				eventQueue.push(newEvent);
				cout << curTimeStep << ":" << setw(6) << setfill(' ') << reqID << " issue " << curEventTrack << " " << curTrack << endl;
				curTrack = curEventTrack;
				
			}
			else if(event->getState() == IoRequest::FINISH)
			{
				currIoReq->setFinishTime(curTimeStep);
				cout << curTimeStep << ":" << setw(6) << setfill(' ') << reqID << " finish " << curTimeStep-currIoReq->getArrTime() << endl;
			}
			//cout << "currtimestep "<< curTimeStep << " NEXTIOFREETIME " << nextIoFreeTime << endl;;  
			if(curTimeStep >= nextIoFreeTime)
			{
				IoRequest* newReq = sched->getNewRequest();
				if(newReq != NULL)
				{
					Event* newEvent = new Event(newReq->getIoId(), curTimeStep, newReq->getTrack(), IoRequest::ISSUE);
					eventQueue.push(newEvent);
					nextIoFreeTime = curTimeStep + abs(newReq->getTrack() - curTrack);
					
				}
			}
			
		}
	}
	
	void ioReqsInfo()
	{
		cout << "IOREQS INFO"<<endl;
		for (int i =0;i< ioReqList.size(); i++)
		{
			cout << setw(5)<< setfill(' ') << i << ":" << setw(6)<< setfill(' ') <<	 ioReqList[i]->getArrTime();;
			cout << setw(6)<< setfill(' ') << ioReqList[i]->getIssueTime(); 
			cout << setw(6)<< setfill(' ') << ioReqList[i]->getFinishTime() << endl;
		}
	}
	
	void printSummary()
	{
		
	}
};
#endif