
//////////////////////////////

#include "Scheduler.cpp"
#include "Process.cpp"
#include <sstream>
#include <iostream>
#include <queue>
#include <vector>


class Prio : public Scheduler{
	private:
		string name;
		queue<Process*>* activeQueue; 
		queue<Process*>* expiredQueue;

		Process* fetchFromQueue(queue<Process*>* q){
			Process* p = NULL;
			for(int i = 3; i >= 0; i--){
				if(q[i].size() == 0){
					continue;
				}
				p = q[i].front();
				q[i].pop();
				break;
			}
			return p;
		}
	public:
		Prio(int quantum)
		{
			this->quantum = quantum;
			activeQueue = new queue<Process*>[4];
			expiredQueue = new queue<Process*>[4];
		}

		void addProcess(Process* p){
			int dp = p->getDynamicPriority();

			queue<Process*>* queueToAdd = activeQueue; 

			if(dp < 0){
				queueToAdd = expiredQueue;
				p->resetDynamicPriority();
			}

			queueToAdd[p->getDynamicPriority()].push(p);
		};

		Process* getNextProcess(){

			Process* p = fetchFromQueue(activeQueue);

			if(p == NULL){
				queue<Process*>* temp = activeQueue; 
				activeQueue  = expiredQueue;
				expiredQueue = temp;
				p = fetchFromQueue(activeQueue);
			}
			return p;
		}

		int getQuantum()
		{
			return quantum;
		}

};
