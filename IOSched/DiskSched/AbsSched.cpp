#ifndef ABSSCHED_CPP
#define ABSSCHED_CPP
#include <limits.h>
#include "IoRequest.cpp"
using namespace std;

class AbsSched
{
	private:
	
	public:
	AbsSched(){}
	
	virtual void addRequest(IoRequest* ioRequest) = 0;
	virtual IoRequest* getNewRequest(int curEventTrack) =0;
};

#endif
