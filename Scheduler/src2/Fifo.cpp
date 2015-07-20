
//////////////////////////////

#include "Scheduler.cpp"

class Fifo : public Scheduler
{
	private:
	queue<Process*> readyQueue;
	
	public:
	
	Fifo(int quantum)
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
		//cout << "ready queue size "<< readyQueue.size() << endl;
	}


	Process* getNextProcess()
	{
		if (readyQueue.size() ==0)
		{
			return NULL;
		}
		
		Process* newProcess = readyQueue.front();
		readyQueue.pop();
		return newProcess;
	}
	
	int getQuantum()
	{
		return quantum;
	}
};