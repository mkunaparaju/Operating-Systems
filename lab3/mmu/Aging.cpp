#ifndef AGING_CPP
#define	AGING_CPP

using namespace std;


class Aging: public AbstractAlgo
{
	private:
		vector<unsigned int> count;
		
	public:
		Aging(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage): AbstractAlgo(ptable, ftable,ftopage)
		{
			//cout << "in aging algo" << endl;
		}
		
		int getNewFrame()
		{
			int pageNum =-1;
			int frameNum =-1;
			int rbit;
			unsigned int counter;
			
			if(count.size() ==0){
				//cout << "creating count of size " << frameTable->size() << endl;
				count = vector<unsigned int> (frameTable->size(),0);
			}
			for (int i=0; i<frameTable->size(); i++)
			{
				frameNum = frameTable->at(i);
				pageNum = frameToPage->at(frameNum);
				rbit = (pageTable->at(pageNum))->referenced;
				counter = count[frameNum];
				counter = (counter >>1 | rbit <<31);
				count[frameNum] = counter;
				(pageTable->at(pageNum))->referenced = 0;
			}
			
			unsigned int min = 0xffffffff;
			unsigned int temp;
			int minIndex = 0;

			for(int i = 0; i < count.size(); i++)
			{
				frameNum = frameTable->at(i);
				temp = count[i];
				//cout << " iterating to find min " << temp  << " " << frameNum << endl;
				if(temp <  min)
				{
					min = temp;					
					minIndex = i;
				}
			}
			count[minIndex] = 0;
			return frameTable->at(minIndex);
		}		
		void updateFrame(int frameNum){}
};

#endif
