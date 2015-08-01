#ifndef SCHEDULERS_CPP
#define SCHEDULERS_CPP
#include <queue>
#include "AbsSched.cpp"

using namespace std;

class Fifo: public AbsSched
{

	private:
	queue<IoRequest*> ioReqQueue;
	
	public:
	
	void addRequest(IoRequest* ioRequest)
	{
		if(ioRequest == NULL)
		{
			return;;
		}
		ioReqQueue.push(ioRequest);
	}
	
	IoRequest* getNewRequest(int curEventTrack)
	{
		if(ioReqQueue.size() == 0)
		{
			return NULL;
		}
		
		IoRequest* ioRequest  = ioReqQueue.front();
		ioReqQueue.pop();
		
		return ioRequest;
	}
};



#endif