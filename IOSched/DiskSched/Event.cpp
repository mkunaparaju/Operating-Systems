#ifndef EVENT_CPP
#define EVENT_CPP
#include "IoRequest.cpp"

using namespace std;

class Event
{
	private:
	int ioId;
	int timeStep;
	int track;
	static int eid;
	int eCounter;
	IoRequest::states state;
	public:
	
	Event(int ioId, int timeStep, int track, IoRequest::states state)
	{
		this->ioId = ioId;
		this->timeStep= timeStep;
		this->track = track;
		this-> state= state;
		this-> eCounter = eid++;
	}

	int getEid()
	{
		return eCounter;
	}	
	int getTimeStep()
	{
		return timeStep;
	}
	void setTimeStep(int timeStep)
	{
		this->timeStep= timeStep;
	}
	
	int getTrack()
	{
		return track;
	}
	void setTrack(int track)
	{
		this->track = track;
	}
	int getIoId()
	{
		return ioId;
	}
	IoRequest::states getState()
	{
		return state;
	}
	void setState(IoRequest::states state)
	{
		this->state = state;
	}

};
int Event::eid =0;
#endif

