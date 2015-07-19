#ifndef FIFO_CPP
#define FIFO_CPP
using namespace std;;

class Fifo : public AbstractAlgo
{
	private:
	
	
	public:
	Fifo(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage) : AbstractAlgo(ptable, ftable, ftopage)
	{
		//cout << " in fifo " << endl;
	}
	
	int getNewFrame()
	{
		int frame =0;
		//cout << "the frame table size is " << frameTable->size() << endl;
		frame = frameTable->front();
		frameTable->erase(frameTable->begin());
		frameTable->push_back(frame);
		//cout << "the frame is " << frame << endl;
		return frame;
		
	}
};
#endif