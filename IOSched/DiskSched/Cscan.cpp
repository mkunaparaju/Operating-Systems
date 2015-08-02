#ifndef CSCAN_CPP
#define	CSCAN_CPP


#include <vector>
#include <limits.h>

using namespace std;

class Cscan : public AbsSched
{
	private:
	vector<IoRequest*> ioReqQueue;
	

	public:
	Cscan()
	{
		
	}
	
	void addRequest(IoRequest* req)
	{
		int loc = ioReqQueue.size();
		for(int i = 0; i < ioReqQueue.size(); i++)
		{
			if(req->getTrack() < ioReqQueue[i]->getTrack()){
			loc = i;
			break;
        }
      }
      ioReqQueue.insert(ioReqQueue.begin() + loc, req);
    }
	
	
	
	IoRequest* getNewRequest(int curEventTrack)
	{		
		int locErase =0;
		IoRequest* ioReturn;
		if(ioReqQueue.size() == 0)
		{
			return NULL;
		}
		
		for(int i = 0; i<ioReqQueue.size();i++)
		{
			if(ioReqQueue[i]->getTrack() < curEventTrack)
			{
				continue;
			}
			
			locErase = i;
			break;
			
		}
		ioReturn = ioReqQueue.at(locErase);
		ioReqQueue.erase(ioReqQueue.begin()+locErase);
		return ioReturn;
		
	}
};
#endif