#ifndef ABSTRACT_ALGO
#define ABSTRACT_ALGO

#include <vector>
#include "pte.cpp"
#include "RandNum.cpp"

using namespace std;

class AbstractAlgo
{
	protected:
		vector<Pte*>* pageTable;
		vector<unsigned int>* frameTable;
		vector<unsigned int>* frameToPage;

	public: 

		AbstractAlgo(vector<Pte*>* ptable, vector<unsigned int>*ftable, vector<unsigned int>* ftopage)
		{
			this->pageTable = ptable;
			this->frameTable = ftable;
			this->frameToPage = ftopage;	
		}

		virtual int getNewFrame() = 0;

};
#endif
