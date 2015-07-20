
//////////////////////////////

#include "Scheduler.cpp"

class RoundRobin : public Scheduler
{
	private:
	queue<Process*> readyQueue;
	
	public:
	
	RoundRobin(int quantum)
	{
		this->quantum = quantum;
	}

	void addProcess(Process* process)
	{
		if (process == NULL)
		{
			//cout << "trying to addnull inside readyqueue" << endl;
			return;
		}
		process->resetDynamicPriority();
		readyQueue.push(process);
		//cout << process->getPid() << "add process pid " << " ready queue size is  " << readyQueue.size() << endl;
	}
	

	Process* getNextProcess()
	{
		if (readyQueue.size() == 0)
		{
			//cout << " ready queue size is null" << endl;
			return NULL;
			
		}
		Process* newProcess = readyQueue.front();
		//cout <<" get process pid"<< endl	;
		readyQueue.pop();
		
		return newProcess;
	}
	
	int getQuantum()
	{
		return quantum;
	}
};