#ifndef SCHEDULERS_CPP
#define SCHEDULERS_CPP
#include <queue>
#include "AbsSched.cpp"

using namespace std;

class Fifo: public AbsSched
{
	private:
	queue<IoRequest*> readyQueue;
	
	public:
	
	void addRequest(IoRequest* ioRequest)
	{
		if(ioRequest == NULL)
		{
			return;;
		}
		readyQueue.push(ioRequest);
	}
	
	IoRequest* getNewRequest()
	{
		if(readyQueue.size() == 0)
		{
			return NULL;
		}
		
		IoRequest* ioRequest  = readyQueue.front();
		readyQueue.pop();
		
		return ioRequest;
	}
};

#endif