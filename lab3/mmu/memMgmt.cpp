#include <vector>
#include "pte.cpp"

using namespace std;

class memMgmt
{
	private:
	vector<pte>* pageTable;
	vector<int>* frameTable;
	vector<int>* frameToPage;

	public: 
	
	memMgmt(vector<pte>* ptable, vector<int>*ftable, vector<int>* ftopage)
	{
		this->pageTable = ptable;
		this->frameTable = ftable;
		this->frameToPage = ftopage;
	}
	
};