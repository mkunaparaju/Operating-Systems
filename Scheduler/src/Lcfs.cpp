
//////////////////////////////
#include <stack>
#include "Scheduler.cpp"

class Lcfs : public Scheduler
{
	private:
	stack<Process*> readyQueue;
	
	public:
	
	
	Lcfs(int quantum)
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
	}


	Process* getNextProcess()
	{
		if (readyQueue.size() ==0)
		{
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