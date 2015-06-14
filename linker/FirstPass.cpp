#include <string>

using namespace std;

class FirstPass
{
	private:
	fstream* fin;
	long fileSize;
	int modCount;	
	int baseAddr;
	int progCount;
	
	public:
	FirstPass (fstream* in, long fSize)
	{
		this->fin = in;
		this->fileSize = fSize;
		modCount = 1;
		baseAddr = 0;
		progCount = 0;
	}
	
	
void doFirstPass(fstream* in, long fSize)
	 {
		SingleModule* oneMod = new SingleModule(in, fSize);
	
		while(!(in->eof()))
		{
			//cout << "starting to read module" << endl;
			
			oneMod->readDefList(modCount, baseAddr);
			if (in->eof())
			{
				break;
			}
			oneMod->readUseList();
			progCount = oneMod->readProgramText();
			baseAddr = baseAddr + progCount;
			cout << " the modCount of this input is " << modCount <<  " baseaddr " << baseAddr<<  endl;
			modCount++;
		}

		
		//cout << "finished reading modules.  Exiting" << endl;
	 }
	
};