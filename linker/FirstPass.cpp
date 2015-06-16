#include <string>	
#include "SecondPass.cpp"

using namespace std;

class FirstPass
{
	private:
	fstream* fin;
	long fileSize;
	int modCount;	
	int baseAddr;
	int progCount;
	SymbolList* sl;
	int useCount;
	
	
	public:
	FirstPass (fstream* in, long fSize, SymbolList* sl )
	{
		this->fin = in;
		this->fileSize = fSize;
		modCount = 1;
		baseAddr = 0;
		progCount = 0;
		this->sl = sl;
		useCount = 0;
	}	
	
	
void doFirstPass()
	 {
		SingleModule* oneMod = new SingleModule(fin, fileSize);
	
		while(!(fin->eof()))
		{
			//cout << "starting to read module" << endl;
			
			//cout << "Symbol list is " << &(sl) << endl;
			sl->checkDef(modCount, progCount);
			oneMod->readDefList(modCount, baseAddr, sl);
			if (fin->eof())
			{
				break;
			}
			oneMod->readUseList();
			progCount = oneMod->readProgramText(modCount);
			baseAddr = baseAddr + progCount;
			sl->checkDef(modCount, progCount);
			
			//cout << " the modCount of this input is " << modCount <<  " baseaddr " << baseAddr<<  endl;
			modCount++;			
			
			
		}

		//cout << "finished reading modules.  Exiting" << endl;
	 }
	 
	 void doSecondPass()
	{
		 //cout << " in second pass "<< endl; 
		 
		 SecondPass* sp = new SecondPass(fin, fileSize);
		
		// if( in->eof())
			
			// {
				// cout << "ed of file " << endl;
			// }
			cout << endl << "Memory Map" << endl;
		while(!(fin->eof()))
		{
			//cout << " second pass while loop" << endl;
			sp->readDefList();
		//	cout << "finished reading def list" << endl;
			if (fin->eof())
			{
				break;
			}
			//cout << "going to read use list" << endl;
			map<int, string> useMap = sp->readUseList();
			
			progCount = sp->readProgText(modCount, baseAddr, useMap, sl);
			baseAddr =baseAddr + progCount;
			modCount++;
					
		}
		
	}
	
};