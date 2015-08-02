#ifndef FSCAN_CPP
#define FSCAN_CPP

#include "AbsSched.cpp"
#include <vector>
#include <limits.h>

using namespace std;

class FSCAN: public AbsSched
{
	
  private:
    vector<IoRequest*>* request_list;
    vector<IoRequest*>* buffer_list;

    vector<IoRequest*> list_one;
    vector<IoRequest*> list_two;

    bool positive;

  public:
    FSCAN()
	{
		positive = true;
		buffer_list = &list_one;
		request_list = &list_two;
    }

    void addRequest(IoRequest* req)
	{
		int loc = buffer_list->size();
		for(int i = 0; i < buffer_list->size(); i++)
		{
			if(req->getTrack() < buffer_list->at(i)->getTrack())
			{
				loc = i;
				break;
			}
		}
		buffer_list->insert(buffer_list->begin() + loc, req);
    }
	
    IoRequest* getNewRequest(int track_location)
	{

		if(request_list->size() == 0 && buffer_list->size() == 0)
		{
			return NULL;
		}
      
      if(request_list->size() == 0)
		{
			vector<IoRequest*>* temp = request_list;
			request_list = buffer_list;
			buffer_list = temp;
			positive = true;
		}
		
		IoRequest *minToLeft = NULL, *minToRight = NULL, *ioToReturn = NULL;
		int locToErase = -1;
		int minLeftDistance = INT_MAX, minRightDistance = INT_MAX, leftLoc = -1, rightLoc = -1;
		unsigned int track_distance;
		bool skip = false;
		for(int i=0; i < request_list->size(); i++)
		{
			track_distance = abs(request_list->at(i)->getTrack() - track_location);
			if(track_distance == 0)
			{
				skip = true;
				locToErase = i;
				ioToReturn = request_list->at(i);
				break;
			}
        //cout << request_list[i]->getTrackumber() << ":" << track_distance << " ";
			if(request_list->at(i)->getTrack() < track_location)
			{
				if(track_distance < minLeftDistance)
				{
					minToLeft = request_list->at(i);
					leftLoc = i;
					minLeftDistance = track_distance;
				}
			}
			else
			{
				if(track_distance < minRightDistance)
				{
					minToRight = request_list->at(i);
					rightLoc = i;
					minRightDistance = track_distance;
				}
			}
		}
      //cout << endl;

		if(!skip)
		{
			if(positive && minToRight == NULL){
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

      request_list->erase(request_list->begin() + locToErase);

      return ioToReturn;
    }

};

#endif