#ifndef PROCESS_CPP
#define PROCESS_CPP
//////////////////////////////////

using namespace std;

class Process
{
private:
	int arrTime;
	int cpuTime;
	int cpuBurst;
	int ioBurst;
	int pid;
	//int prio;
	int remTime;
	int currStateTime;
	int remCpuBurst;
//	int prevStateTime;
	int lastTransTime;
	int eid;
	int ioTime;
	int cpuWaitTime;
	int staticPriority;
	int dynamicPriority;
	
public:
	enum states
	{
		CREATED =1,
		READY =2,
		BLOCKED = 3,
		RUNNING =4,
		DONE=5
	};

	Process(int arrTime, int cpuTime, int cpuBurst, int ioBurst, int pid, int prio)
	{
		this->arrTime = arrTime;
		this->cpuTime = cpuTime;
		this->cpuBurst = cpuBurst;
		this->ioBurst = ioBurst;
		this->pid = pid;
		//this->prio = prio;
		this->remTime = cpuTime;
		this->currStateTime =0;
		this->remCpuBurst=0;
		lastTransTime = arrTime;
		eid =0;
		ioTime =0;
		cpuWaitTime =0;
		this->staticPriority = prio;
		this->dynamicPriority= prio - 1;
	}

	int getPid()
	{
		return pid;
	}
	// int getPrio()
	// {
		// return prio;
	// }

	int getArrTime()
	{
		return arrTime;
	}

	int getCpuTime()
	{
		return cpuTime;
	}

	int getCpuBurst()
	{
		return cpuBurst;
	}
	int getIoBurst()
	{
		return ioBurst;
	}
	int getRemTime()
	{
		return remTime;
	}
	void setRemTime(int remTime)
	{
		this->remTime = remTime;
	}
	
	int getCurrStateTime()
	{
		return currStateTime;
	}
	void setCurrStateTime(int currStateTime)
	{
		this->currStateTime = currStateTime;
	}
	int getRemCpuBurst()
	{
		return remCpuBurst;
	}
	void setRemCpuBurst(int remCpuBurst)
	{
		this->remCpuBurst = remCpuBurst;
	}
	int getLastTransTime()
	{
		return lastTransTime;
	}
	void setLastTransTime(int lastTransTime)
	{
		this->lastTransTime = lastTransTime;
	}
	int getEid()
	{
		return eid;
	}
	int setEid(int eid)
	{
		this->eid = eid;
	}
	int getIoTime()
	{
		return ioTime;;
	}
	void setIoTime(int ioTime)
	{
		this->ioTime = ioTime;
	}
	
	int getCpuWaitTime()
	{
		return cpuWaitTime;
	}
	void setCpuWaitTime(int cpuWaitTime)
	{
		this->cpuWaitTime = cpuWaitTime;
	}
	void reduceDynamicPriority(){
	  this->dynamicPriority--;
	}

	void resetDynamicPriority(){
	  this->dynamicPriority = staticPriority - 1;
	 // cout << dynamicPriority << "dynamic priority  resettimg" << endl;
	}

	int getDynamicPriority(){
		//cout << dynamicPriority << "dunamic priority" << endl;
	  return dynamicPriority;
	}

	int getStaticPriority(){
	  return staticPriority;
	}
	// int getPrevStateTime()
	// {
		// return prevStateTime;
	// }
	// void setPrevStateTime(int prevStateTime)
	// {
		// this->prevStateTime = prevStateTime;
	// }
	
};

#endif
