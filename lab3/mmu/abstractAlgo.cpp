#include <vector>
#include "pte.cpp"
using namespace std;

class abstractAlgo
{
	private:
	vector<pte>* pageTable;
	vector<int>* frameTable;
	vector<int>* frameToPage;

	public: 
	
	abstractAlgo(vector<pte>* ptable, vector<int>*ftable, vector<int>* ftopage)
	{
		this->pageTable = ptable;
		this->frameTable = ftable;
		this->frameToPage = ftopage;
	}
	
};