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

		int getNewFrame()
		{
			int frameNum = -1;

			while(true) 
			{				
				frameNum = (pageTable->at(pointer))->pageFrameNum;
			
				if((pageTable->at(pointer))->present == 1)
				{
					cout << "the frame number "<< frameNum << " the page index "<< frameToPage->at(frameNum) << endl;
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

class LRU: AbstractAlgo
{
	private:
	public: 
	LRU(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage) : AbstractAlgo(ptable, ftable, ftopage)	
	{		
		
	}
	
	int getNewFrame()
	{
		int frame
	}
}

#endif
