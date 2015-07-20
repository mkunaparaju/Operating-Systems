#ifndef TRANSITION_CPP
#define TRANSITION_CPP
////////////////////////////////////


#include <queue>
#include <iomanip>
#include "Event.cpp"
#include "RandNum.cpp"
#include "Scheduler.cpp"
#include "Process.cpp"
using namespace std;

struct eventComparator
{
	bool operator()(Event* lhs, Event* rhs) const
	{

		if(lhs->getTimeStamp() != rhs->getTimeStamp()){
			return lhs->getTimeStamp() > rhs->getTimeStamp();
		}
		return lhs->getEid() > rhs->getEid();
		/*
		if (lhs->getTimeStamp() == rhs->getTimeStamp())
		{
			if (lhs->getEid() > rhs->getEid())
			{
				return true;
			}
		}
		else if (lhs->getTimeStamp() > rhs->getTimeStamp())
			return true;

		else
			return false;
		*/
	}
};

class Transition
{
	private:

		priority_queue<Event*, vector<Event*>, eventComparator> eventQueue;
		vector<Process*> processList;
		RandNum* rn;
		Scheduler* sched;
		double totalIoNoOverlap;
		bool vFlag;

	public:

		Transition(priority_queue<Event*, vector<Event*>, eventComparator> eventQueue,vector<Process*> processList, RandNum* rn, Scheduler* sched, bool vFlag)
		{
			this->eventQueue = eventQueue;
			this->processList= processList;
			this->rn = rn;
			this->sched = sched;
			this->totalIoNoOverlap =0;
			this->vFlag = vFlag;;
			//cout << eventQueue.size() << "constructor"<< endl;
		}

		void transLogic( )
		{
			int nextCpuFreeTime=0;
			int iob;
			int cb;
			int remCpuBurst;
			int allowedTime;			
			int remTime;
			int ioTime;;
			int cpuWaitTime;
			int totalIOB;
			int iobStart;
			int ioInProgress = 0;		

			Process::states newState;
			//cout << "inside transLogic " << eventQueue.size() << endl;
			int timeStamp = 0;
			while (eventQueue.size() > 0)
			{ 

				Event* event =  eventQueue.top();
				timeStamp = event->getTimeStamp();

				while(eventQueue.size() > 0 && timeStamp == (eventQueue.top())->getTimeStamp())
				{
					event =  eventQueue.top();
					eventQueue.pop();
					Process* process = processList[event->getPid()];	
					timeStamp = event->getTimeStamp();
					process->setEid(event->getEid());

					if(event->getPrevState() == Process::CREATED && event->getNewState() == Process::READY)
					{
						if (vFlag)
						{						
							cout << event->getTimeStamp() << " " << event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "CREATED" << " -> " << "READY" << endl;  
						}
						sched->addProcess(process);
					}

					else if(event->getPrevState() == Process::BLOCKED && event->getNewState() == Process::READY)
					{
						ioInProgress--;
						if(ioInProgress == 0)
						{
							totalIoNoOverlap += (event->getTimeStamp() - iobStart);
						}
						ioTime = process->getIoTime();
						process->setIoTime(ioTime+ timeStamp-process->getLastTransTime());
						if(vFlag)
						{
							cout << event->getTimeStamp() << " " << event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "BLOCK" << " -> " << "READY" << endl;  
						}
						sched->addProcess(process);

					}
					else if(event->getPrevState() == Process::RUNNING && event->getNewState() == Process::READY)
					{
						if(vFlag)
						{
							cout << event->getTimeStamp() << " " << event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "RUNNG" << " -> " << "READY" << "  cb=" << process->getRemCpuBurst() << " rem=" << process->getRemTime() <<" prio=" << process->getDynamicPriority() << endl ;  
						}
						sched->addProcess(process);
					}
					else if(event->getPrevState() == Process::RUNNING && event->getNewState() == Process::DONE)
					{
						if(vFlag)
						{
							cout << event->getTimeStamp() << " " << event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "Done" << endl;  
						}
					}
					else if (event->getPrevState() == Process::RUNNING && event->getNewState() == Process::BLOCKED)
					{
						ioInProgress++;
						int randomNum = rn->getRandNum();
						iob = 1 + (randomNum % (process->getIoBurst()));
						if(ioInProgress == 1)
						{
							iobStart = event->getTimeStamp();
						}

						if(vFlag)
						{
							cout << event->getTimeStamp() << " " << event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "RUNNG" << " -> " << "BLOCK " << " ib=" << iob << " rem=" << process->getRemTime() << endl;
						}
						Event* newEvent = new Event(event->getPid(), (event->getTimeStamp()+iob), Process::BLOCKED, Process::READY);
						eventQueue.push(newEvent);
						process->resetDynamicPriority();
					}
					else if(event->getPrevState() == Process::READY && event->getNewState() == Process::RUNNING)
					{
						if(process->getRemCpuBurst() == 0)
						{					
							int randomNum = rn->getRandNum();
							cb = 1 + (randomNum % (process->getCpuBurst()));
							if (cb < process->getRemTime())
							{
								process->setRemCpuBurst(cb);
							}
							else
							{
								process->setRemCpuBurst(process->getRemTime());
							}
						}
						remCpuBurst = process->getRemCpuBurst();
						if(remCpuBurst > sched->getQuantum())
						{

							allowedTime = sched->getQuantum();
							remCpuBurst = remCpuBurst-allowedTime;
							newState =Process::READY;
						}
						else
						{
							//cout << "blocked if loop " << endl;
							allowedTime= remCpuBurst;
							remCpuBurst =0;
							newState = Process::BLOCKED;
						}

						if(allowedTime >= process->getRemTime())
						{
							allowedTime = process->getRemTime();
							newState = Process::DONE;
						}
						cpuWaitTime = process->getCpuWaitTime();
						process->setCpuWaitTime(cpuWaitTime+ timeStamp-process->getLastTransTime());
						if(vFlag)
						{
							cout << event->getTimeStamp() << " "<< event->getPid() << " "<< timeStamp-process->getLastTransTime() << ": " << "READY" << " -> " <<"RUNNG" << " cb=" << remCpuBurst+allowedTime << " rem=" << process->getRemTime() << " prio=" << process->getDynamicPriority()+1 << endl;
						}
						nextCpuFreeTime = timeStamp+ allowedTime;
						remTime = process->getRemTime();
						process->setRemCpuBurst(remCpuBurst);
						process->setRemTime(remTime-allowedTime);
						process->reduceDynamicPriority();
						Event *newEvent = new Event(event->getPid(), (event->getTimeStamp()+allowedTime), Process::RUNNING, newState);
						eventQueue.push(newEvent);
					}	
					process->setLastTransTime(event->getTimeStamp());
				}

				//cout << "exiting outer loop" << endl;

				//cout << "timestamp " << timeStamp << "nextcpufreetime "<< nextCpuFreeTime << endl;
				if(timeStamp >= nextCpuFreeTime )
				{
					//cout << "EXT cpu free time"<< endl;
					Process* newProcess = sched->getNextProcess();
					if(newProcess != NULL)
					{						
						int pid = newProcess->getPid();
						//cout << "pid "<< pid << endl;
						Event* newEvent = new Event(pid, timeStamp, Process::READY, Process::RUNNING);
						eventQueue.push(newEvent);
						//newProcess->setEid(newEvent->getEid());
					}else{
						//cout << ";;;;;;" << endl;
					}
				}

				//cout << "exiting main while looop" << endl;
			}
		}

		void summary(string schedName)
		{
			cout << schedName << endl;

			for (int i = 0; i < processList.size(); i++)
			{
				Process* p = processList[i];
				cout << setfill('0') << setw(4) << p->getPid() << ": ";
				cout << setfill(' ') << setw(4) << p->getArrTime();
				cout << " " << setfill(' ') << setw(4) << p->getCpuTime();
				cout << " " << setfill(' ') << setw(4) << p->getCpuBurst();
				cout << " " << setfill(' ') << setw(4) << p->getIoBurst();
				cout << " " << p->getStaticPriority();
				cout << " | ";
				cout << setfill(' ') << setw(5) << p->getLastTransTime() << " ";
				cout << setfill(' ') << setw(5) << p->getLastTransTime()- p->getArrTime() << " ";
				cout << setfill(' ') << setw(5) << p->getIoTime() << " ";
				cout << setfill(' ') << setw(5) << p->getCpuWaitTime();
				cout << endl;
			}

		}

		void finalSummary()
		{
			double totalCpu, averageTurnAround, averageWaitTime, throughput;
			int lastFinishTime=0, totalTurnAroundTime = 0, totalWaitTime = 0;

			for (int i = 0; i < processList.size(); i++)
			{
				Process* p = processList[i];


				if(lastFinishTime < p->getLastTransTime())
				{
					lastFinishTime = p->getLastTransTime();
				}
				totalCpu =  totalCpu+ p->getCpuTime()	;
				totalTurnAroundTime = totalTurnAroundTime + (p->getLastTransTime()- p->getArrTime());
				totalWaitTime = totalWaitTime + p->getCpuWaitTime();

			}
			averageTurnAround = (double)totalTurnAroundTime/(double)processList.size();
			averageWaitTime = (double)totalWaitTime/(double)processList.size();
			throughput = (double)processList.size()/((double)lastFinishTime/100);

			printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n",
					lastFinishTime,
					((double)totalCpu/lastFinishTime)*100,
					((double)totalIoNoOverlap/lastFinishTime)*100,
					averageTurnAround,
					averageWaitTime,
					throughput);
		}
};
#endif
