#ifndef PR_ALGOS
#define PR_ALGO

using namespace std;;

class Random: public AbstractAlgo
{
	private:
		RandNum* rn;
	public:
		Random(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage, RandNum* rn): AbstractAlgo(ptable, ftable,ftopage)
	{
		this->rn = rn;
	}
		void updateFrame(int frameNum){}
		int getNewFrame()
		{
			return (rn->getRandNum())% (frameTable->size());
		}

};;

class SecondChance : public AbstractAlgo
{
	private:


	public:
		SecondChance(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage) : AbstractAlgo(ptable, ftable, ftopage)
	{
	}
		void updateFrame(int frameNum){}
		int getNewFrame()
		{
			//	cout << "inside 2nd cance"<< endl;
			int frameNum =-1;
			int pageNum =-1;
			bool reference= false;
			while(true)
			{
				frameNum = frameTable->front();
				pageNum = frameToPage->at(frameNum);
				reference = (pageTable->at(pageNum))->referenced;
				frameTable->erase(frameTable->begin());
				frameTable->push_back(frameNum);
				if (reference == false )
				{
					//return frameNum;;
					break;
				}	
				(pageTable->at(pageNum))->referenced = 0;
			}
			return frameNum;
		}

};


class Clock: public AbstractAlgo
{
	private:
		int pointer;
	public:
		Clock(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage): AbstractAlgo(ptable, ftable,ftopage)
	{
		pointer =-1;
	}
		void updateFrame(int frameNum){}
		
		int getNewFrame() {
			int frameNum = -1;
			int pageNum = -1;
			bool reference = true;

			while(true) {
				pointer = (++pointer % (frameTable->size()));

				frameNum = frameTable->at(pointer);

				pageNum =frameToPage->at(frameNum);

				reference = (pageTable->at(pageNum))->referenced;
				(pageTable->at(pageNum))->referenced = false;

				//cout << "pointer is " << pointer << " frameNum is " << frameNum << " pageNum is " << pageNum << endl;

				if(reference == false)
				{
					break;
				}
			}
			return frameNum;
		}

};;


class VirtualClock: public AbstractAlgo
{
	private:
		int pointer;
	public:
		VirtualClock(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage): AbstractAlgo(ptable, ftable,ftopage)
		{
			//cout << "Creatinga  vritual clock object " << endl;
			pointer =0;
		}
		void updateFrame(int frameNum){}
		
		
		int getNewFrame()
		{
			int frameNum = -1;

			while(true) 
			{				
				frameNum = (pageTable->at(pointer))->pageFrameNum;
			
				if((pageTable->at(pointer))->present == 1)
				{
					//cout << "the frame number "<< frameNum << " the page index "<< frameToPage->at(frameNum) << endl;
					if((pageTable->at(pointer))->referenced == 0)
					{
						break;;
					}
					(pageTable->at(pointer))->referenced = 0;
				}
				pointer = (pointer+1)%(pageTable->size());
				
			}
				pointer = (pointer+1)%(pageTable->size());
			return frameNum;
		}
};;

class LRU: public AbstractAlgo
{
	private:
	public: 
	LRU(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage) : AbstractAlgo(ptable, ftable, ftopage)	
	{		
		
	}
	
	int getNewFrame()
	{
		int frameNum = frameTable->front();
		frameTable->erase(frameTable->begin());
		frameTable->push_back(frameNum);
		return frameNum;
	}
	void updateFrame(int frameNum)
	{
		for(int i=0; i<frameTable->size(); i++)
		{
			if(frameTable->at(i) == frameNum)
			{
				frameTable->erase(frameTable->begin() +i);
				frameTable->push_back(frameNum);
			}
		}
	}
};
class NRU: public AbstractAlgo
{
	private:
	RandNum* rn;
	int counter;;
	public:
	
	NRU(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage, RandNum* rn) : AbstractAlgo(ptable, ftable, ftopage)
	{
		//cout << "in NRU" << endl;
		counter =0;;
		this->rn = rn;
	}
	void updateFrame(int frameNum){}
	int getNewFrame()
	{

		int frameNum=-1;
		vector<Pte*> *pClass = new vector<Pte*>[4];
		
		for(int i =0; i<pageTable->size(); i++)
		{
					
			if((pageTable->at(i))->present == 1)
			{

				if((pageTable->at(i))->referenced == 0 && (pageTable->at(i))->modified == 0)
				{
					
					pClass[0].push_back(pageTable->at(i));
				}
				else if((pageTable->at(i))->referenced == 0 && (pageTable->at(i))->modified == 1)
				{
							
					pClass[1].push_back(pageTable->at(i));
				}
				else if((pageTable->at(i))->referenced == 1 && (pageTable->at(i))->modified == 0)
				{
							
					pClass[2].push_back(pageTable->at(i));
				}
				else if((pageTable->at(i))->referenced == 1 && (pageTable->at(i))->modified == 1)
				{
							
					pClass[3].push_back(pageTable->at(i));
				}			
			}			
		}

		for (int i =0; i< 4; i++)
		{
			//cout << " 2nd for loop before if"<< endl;
			if(!(pClass[i].empty())) 
			{
				//cout << " 2nd for loop] "<< endl;
				int refNum = (rn->getRandNum()) % pClass[i].size();
				Pte* page = pClass[i][refNum];
				frameNum = page->pageFrameNum;
			//	frameTable->erase(frameTable->begin() + frameNum);
			//	frameTable->push_back(frameNum);				
				
				break;
			}
		}
			counter++;
			if (counter%10 ==0)
				{
					for(int i =0; i<pageTable->size(); i++)
					{	
						if((pageTable->at(i))->present == 1)
						(pageTable->at(i))->referenced = 0;
					}
				}
				
			return frameNum;
	
	}
};
#endif
