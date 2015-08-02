#ifndef ELEVATOR_CPP
#define ELEVATOR_CPP

#include <vector>
#include <limits.h>

using namespace std;

class Elevator : public AbsSched
{
	private:
	vector<IoRequest*> ioReqQueue;
	bool positive;

	public:
	Elevator()
	{
		positive = true;
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
		if(ioReqQueue.size() == 0)
		{
			return NULL;
		}
      IoRequest *minToLeft = NULL, *minToRight = NULL, *ioToReturn = NULL;
      int locToErase = -1;
      int minLeftDistance = INT_MAX, minRightDistance = INT_MAX, leftLoc = -1, rightLoc = -1;
      unsigned int track_distance;
      bool skip = false;
      for(int i=0; i < ioReqQueue.size(); i++)
	  {
		track_distance = abs(ioReqQueue[i]->getTrack() - curEventTrack);
        if(track_distance == 0)
		{
          skip = true;
          locToErase = i;
          ioToReturn = ioReqQueue[i];
          break;
        }
        //cout << ioReqQueue[i]->getTrackNumber() << ":" << track_distance << " ";
        if(ioReqQueue[i]->getTrack() < curEventTrack)
		{
			
			if(track_distance < minLeftDistance)
			{
				minToLeft = ioReqQueue[i];
				leftLoc = i;
				minLeftDistance = track_distance;
			}
        }
		else
		{
			if(track_distance < minRightDistance)
			{
				minToRight = ioReqQueue[i];
				rightLoc = i;
				minRightDistance = track_distance;
          }
        }
      }
      //cout << endl;

      if(!skip)
	  {
        if(positive && minToRight == NULL)
		{
			ioToReturn = minToLeft;
			locToErase = leftLoc;

			positive = !positive;
        }
		else if(positive && minToRight != NULL)
		{
			ioToReturn = minToRight;
			locToErase = rightLoc;
        }
		else if(!positive && minToLeft == NULL)
		{
			ioToReturn = minToRight;
			locToErase = rightLoc;

			positive = !positive;
        }
		else
		{
			ioToReturn = minToLeft;
			locToErase = leftLoc;
        }
      }

		ioReqQueue.erase(ioReqQueue.begin() + locToErase);

		return ioToReturn;
		
	}
};

#endif