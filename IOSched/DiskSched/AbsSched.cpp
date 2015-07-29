#ifndef ABSSCHED_CPP
#define ABSSCHED_CPP

using namespace std;

class AbsSched
{
	private:
	
	public:
	AbsSched()
	{
		
	}
	
	virtual void addRequest(IoRequest* ioRequest ) = 0;
	virtual IoRequest* getNewRequest(void) =0;
};

#endif
