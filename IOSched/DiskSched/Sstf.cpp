#ifndef SSTF_CPP
#define SSTF_CPP

#include <queue>
#include "AbsSched.cpp"
#include <limits.h>

using namespace std;

class Sstf :public AbsSched
{
	private:
	int curTrack;
	vector<IoRequest*> ioReqQueue;
	
	public:
	Sstf()
	{
		curTrack =0;
	}
	
	void addRequest(IoRequest* ioRequest)
	{
		
		if(ioRequest == NULL)
		{
			return;;
		}
		ioReqQueue.push_back(ioRequest);
		
	}
	
	IoRequest* getNewRequest(int curEventTrack)
	{
		curTrack = curEventTrack;
		int leastDist = INT_MAX;
		int leastLoc = 0;
		if(ioReqQueue.size() <= 0)
		{
			return NULL;	
		}
		for(int i = 0; i< ioReqQueue.size(); i++)
		{
			if(abs(ioReqQueue[i]->getTrack()- curTrack) < leastDist)
			{
				leastDist = abs(ioReqQueue[i]->getTrack()- curTrack);
				leastLoc = i;
			}
				
		}
		IoRequest* ioRequest = ioReqQueue[leastLoc];
		ioReqQueue.erase(ioReqQueue.begin()+ leastLoc);
		
		return ioRequest ;
	}
	
};


#endif