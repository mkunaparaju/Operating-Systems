#include <string>
#include <iomanip>
using namespace std;

class SecondPass
{
	private:
	private:
	fstream* fin;
	long fileSize;
	int count;
	char ch;
	ReaderUtil* util;
	int instrCount;
	
	
	public: 
	SecondPass(fstream* in, long fSize)
	{
		this->fin = in;
		this->fileSize = fSize;
		util = new ReaderUtil(fin, fileSize);
		instrCount =0;
	}
	
	void* readDefList()
	
	{
		//cout << "reading def list " << endl;
		Token<int> newInteger = util->getInteger(true);
		int count = newInteger.getValue();
		//cout << "count is " << count << endl;
		
		while(count-- > 0)
		{
			util->getSymbol();
			util->getInteger(false);
		}		
	}
	
	map<int, string> readUseList()
	{
		Token<int> newInteger = util->getInteger(false);
		int count = newInteger.getValue();
		int useIndex =0;
		map<int, string> useMap;
		
		while(count--)
		{
			Symbol symbol  = util->getSymbol();
			useMap.insert(pair<int, string>(useIndex, symbol.getToken() ));
			useIndex++;
		}
		
		return useMap;

		
	}
	
	int readProgText(int modCount, int baseAddr, map<int,string> useMap, SymbolList* sl)
	{
		Token<int> newInteger = util->getInteger(false);
		int count = newInteger.getValue();
		int progCount = count;
		int opCode =0; 
		int operand =0;
		int newInstr =0;
		int useCount = useMap.size();
		map <string, bool> instrMap;
		string error = "\0";
		//cout << baseAddr  <<" base  addr"<< endl;
		
		while(count--)
		{
			char addr = util->getAddr();
			Token<int> tok = util->getInstr();
			int length = tok.getLength();
			int instr = tok.getValue();
			//cout << "instruction is" <<  instr << endl;
			 opCode = instr/1000;
			 operand = instr%1000; 		 
			 string symbol;
			
				//cout << " operand " << operand  << endl;
			if (addr == 'I' && instr > 9999)
			{
				if(instr > 9999)
				{
					error =  "Error: Illegal immediate value; treated as 9999";
					instr = 9999;
				
				}
				
				
			}
			else if (instr > 9999)
			{
				 error ="Error: Illegal opcode; treated as 9999 ";
				instr = 9999;
			}
			else if(addr == 'R')
			{
				if(operand > progCount)
				{
					error =  "Error: Relative address exceeds module size; zero used"; 
					operand = 0;
				}
				operand = baseAddr + operand;
			}
			else if(addr == 'E')
			{
				if(operand > useCount-1)
				{
					error =  "Error: External address exceeds length of uselist; treated as immediate" ;
					addr = 'I';
				}else{
					
				symbol = useMap[operand];
				//cout << "operand is " << operand << " symbol is " << symbol << endl;
				bool isUsed = sl->isSymbolPresent(symbol);
				
				instrMap.insert(pair<string, bool>(symbol, true));
				
				if (!isUsed)
				{
					error =  "Error: "+ symbol +" is not defined; zero used";
					operand = 0;
				}			
			}
					
			}
			else if(addr == 'A')
			{
				if(operand > 512)
				{
					error ="Error: Absolute address exceeds machine size; zero used";
					operand = 0;
				}
			
			}
			
	//	cout << "returning from prog text read " << endl;
		cout << setfill('0') << setw(3) << instrCount << ": " ;

		switch (addr)
		{
			case 'I':
				cout << setfill('0') << setw(4) << instr << " " << error <<endl;
			break;
			
			case 'A':
				newInstr = (opCode)*1000 + operand;
				cout << setfill('0') << setw(4) <<newInstr <<  " " <<error << endl;
				
			break;
			
			case 'R':
				
				newInstr = (opCode)*1000 + operand;
				cout << setfill('0') << setw(4) << newInstr <<  " " <<error << endl ;
				operand = operand + baseAddr;
			break;
			
			case 'E':
				symbol = useMap[operand];
				operand = sl->getAbAddr(symbol);
				newInstr = (opCode)*1000 + operand;
				cout << setfill('0') << setw(4) << newInstr <<  " " <<error << endl;
				
			break;
			
			default : 
			break;
		}
		instrCount++;
		}	
		for (int i = 0; i<useMap.size(); i++)
			{
				string sym = useMap[i];
				if (!(instrMap.count(sym) > 0))
				{
					cout << "Warning: Module "<<modCount<< ": "<<sym<<" appeared in the uselist but was not actually used "<< endl;
				}
			}
			
	
		return progCount;
	}
};