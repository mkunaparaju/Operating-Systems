
//////////////////////////////

#include "Scheduler.cpp"

struct sjfComparator
{
	bool operator()(Process* lhs, Process* rhs) const
	{
		if(lhs->getRemTime() != rhs->getRemTime()){
			return lhs->getRemTime() > rhs->getRemTime();
		}
		return lhs->getEid() > rhs->getEid();
/*
		if (lhs->getRemTime() == rhs->getRemTime())
		{
			if (lhs->getEid() > rhs->getEid())
			{
				return true;
			}
		}
			else if (lhs->getRemTime() > rhs->getRemTime())
				return true;

			else
				return false;
*/
	}
};

class Sjf : public Scheduler
{
	private:
	priority_queue<Process*, vector<Process*>, sjfComparator> readyQueue;
	
	public:
	
	
	Sjf(int quantum)
	{
		this->quantum = quantum;
	}

	void addProcess(Process* process)
	{
		if(process == NULL){
			return;
		}
		process->resetDynamicPriority();
		readyQueue.push(process);
	}


	Process* getNextProcess()
	{
		if(readyQueue.size() <= 0){
			return NULL;
		}
		Process* newProcess = readyQueue.top();
		readyQueue.pop();
		return newProcess;
	}
	
	int getQuantum()
	{
		return quantum;
	}
};
