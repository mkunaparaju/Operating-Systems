#include <vector>
#include "pte.cpp"
#include "abstractAlgo.cpp"
#include "FIFO.cpp"
#include <iomanip>

using namespace std;

class MemMgmt
{
	private:
		vector<Pte*>* pageTable;
		vector<unsigned int>* frameTable;
		vector<unsigned int>* frameToPage;
		int numFrames;;
		int frameIndex;
		//Pte newPage;
		int currFrameNum;
		int oldFrame;
		int oldPageNum;
		long long instrCounter;
		bool detailPrint;
		bool ptePrint;
		bool ftePrint;
		bool sumPrint;
		long long zero;
		long long map;
		long long unmap;
		long long in;
		long long out;;
		AbstractAlgo* prAlgo; 

	public: 

		MemMgmt(vector<Pte*>* ptable, vector<unsigned int>* ftable, vector<unsigned int>* ftopage, AbstractAlgo* prAlgo, int numFrames)
		{
			this->pageTable = ptable;
			this->frameTable = ftable;
			this->frameToPage = ftopage;
			this->numFrames = numFrames;
			frameIndex = 0;
			oldPageNum =0;;
			oldFrame =0;
			this->prAlgo =prAlgo;
			instrCounter =0;

			detailPrint=false;
			ptePrint = false;;
			ftePrint = false;;
			sumPrint = false;
			zero =0;map=0;unmap=0;in=0; out=0;
		}


		void instrHandle(char operation,int currPageNum)
		{
			if(detailPrint)
			{
				cout << "==> inst: "<< operation << " "<< currPageNum<< endl;
			}

			if((pageTable->at(currPageNum))->present == true)
			{				
				currFrameNum = (pageTable->at(currPageNum))->pageFrameNum;
				prAlgo->updateFrame(currFrameNum);
				
			}
			else
			{

				if(frameTable->size() < numFrames)
				{
					//cout << "here" <<endl;
					if(detailPrint)
					{
						cout <<instrCounter<< ": ZERO " << setfill(' ') << setw(8) << frameIndex << endl;
						cout <<instrCounter<< ": MAP  " <<setfill(' ') << setw(4) << currPageNum  << setw(4) <<frameIndex << endl;
					}
					zero++;
					map++;


					(pageTable->at(currPageNum))->pageFrameNum = frameIndex;
					frameToPage->at(frameIndex) = currPageNum;

					frameTable->push_back(frameIndex);
					frameIndex++;
				}
				else
				{
					getFrameMMU();
					if((pageTable->at(currPageNum))->pagedOut == true)
					{
						if(detailPrint)
						{
							cout <<instrCounter<< ": IN   " <<setfill(' ') << setw(4)<< currPageNum<< setw(4) << oldFrame << endl;
						}
						in++;
						(pageTable->at(currPageNum))->present = true;
					}
					else
					{
						if(detailPrint)
						{
							cout <<instrCounter<< ": ZERO " << setfill(' ') << setw(8)<< oldFrame<< endl;
						}
						zero++;
					}
					if(detailPrint)
					{
						cout <<instrCounter<< ": MAP  " <<setfill(' ') << setw(4) << currPageNum  << setw(4) << oldFrame << endl;
					}
					map++;
					(pageTable->at(currPageNum))->pageFrameNum = oldFrame;
					frameToPage->at(oldFrame) = currPageNum;
				}


			}

			if(operation == '1')
			{
				(pageTable->at(currPageNum))->modified = true;
			}					
			(pageTable->at(currPageNum))->referenced = true;

			(pageTable->at(currPageNum))->present = true;
			instrCounter++;
			//:cout << instrCounter << endl;
		}
		void getFrameMMU()
		{
			oldFrame = prAlgo->getNewFrame();
			oldPageNum = frameToPage->at(oldFrame);
			if(detailPrint)
			{
				cout<< instrCounter<< ": UNMAP" <<setfill(' ') << setw(4)<< oldPageNum << setw(4) << oldFrame << endl;
			}
			unmap++;
			(pageTable->at(oldPageNum))->present = false;
			if((pageTable->at(oldPageNum))->modified == true )
			{
				if(detailPrint)
				{
					cout << instrCounter<< ": OUT  "<<setfill(' ') << setw(4)<< oldPageNum << setw(4) << oldFrame << endl;
				}
				out++;
				(pageTable->at(oldPageNum))->pagedOut = 1;;
				(pageTable->at(oldPageNum))->modified = 0;
			}

		}
		void pageTablePrint()
		{
			if(!ptePrint)
			{
				cout << "ptePrint is not set. returning " << endl;
				return;
			}
			for (int pte = 0; pte < pageTable->size(); pte++) 
			{
				if ((pageTable->at(pte))->present == 1) 
				{
					cout << pte << ":";
					if ((pageTable->at(pte))->referenced == 1) 
					{
						cout << "R" ;
					}
					else
					{
						cout << "-" ;
					}
					if ((pageTable->at(pte))->modified == 1) 
					{
						cout << "M" ;
					}
					else
					{
						cout << "-" ;
					}
					if ((pageTable->at(pte))->pagedOut == 1) 
					{
						cout << "S" ;
					}
					else
					{
						cout << "-" ;
					}

				}
				else
				{
					if ((pageTable->at(pte))->pagedOut == 1) 
					{
						cout << "#" ;
					}
					else
					{
						cout << "*" ;
					}
				}
				cout << " " ;
			}
			cout<<endl;
		}

		void frameTablePrint()
		{
			if(!ftePrint)
			{
				cout << "ftePrint is not set. returning " << endl;
				return;
			}
			for(int i=0; i< frameToPage->size(); i++)
			{
				if(frameToPage->at(i) == -1)
				{
					cout << "* " ;;
				}
				else
				{
					cout << frameToPage->at(i) << " "; 
				}
			}
			cout << endl;
		}

		void summaryPrint()
		{
			if(!sumPrint){
				cout << "sumPrint is not set. returning " << endl;
				return;
			}
			//cout<< "inside summary print" << endl;
			cout << "SUM " << instrCounter << " U=" << unmap  << " M=" << map << " I=" << in << " O=" << out << " Z=" << zero ;
			cout << " ===> " << calcSummary() << endl;
		}

		int calcSummary()
		{
			long long totalCycles = ((map+unmap)*400) + ((in+out)*3000) + (zero*150) + instrCounter;
			return totalCycles;;
		}

		void setDetailPrint(bool detailPrint)
		{
			this->detailPrint = detailPrint;
		}

		void setPtePrint(bool ptePrint)
		{
			this->ptePrint = ptePrint;
		}

		void setFtePrint(bool ftePrint)
		{
			this->ftePrint = ftePrint;
		}	

		void setSumPrint(bool sumPrint)
		{
			this->sumPrint = sumPrint;
		}
};

