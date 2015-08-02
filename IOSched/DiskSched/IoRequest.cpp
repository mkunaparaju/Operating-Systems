#ifndef IOREQUEST_CPP
#define IOREQUEST_CPP

using namespace std;

class IoRequest
{
	private:
	int arrTime;;
	int issueTime;
	int finishTime;
	int ioId;
	int eid;
	int track;
	
	public:
	
	enum states
	{
		ADD ,
		FINISH,
		ISSUE
		
	};
	
	IoRequest(int arrTime, int track, int ioId)
	{
		this-> arrTime = arrTime;
		this->track = track;
		this->ioId = ioId;
	}
	
	int getEid()
	{
		return eid;
	}
	int setEid(int eid)
	{
		this->eid = eid;
	}
	
	int getIoId()
	{
		return ioId;
	}
	
	int getArrTime()
	{
		return arrTime;
	}
	int getIssueTime()
	{
		return issueTime;
	}
	int setIssueTime(int issueTime)
	{
		this->issueTime = issueTime;
	}
	int getFinishTime()
	{
		return finishTime;;
	}
	int setFinishTime(int finishTime)
	{
		this->finishTime = finishTime;
	}
	int getTrack()
	{
		return track;
	}
};
#endif