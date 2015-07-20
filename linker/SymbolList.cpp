

#include <vector>
#include <string>
#include "Token.h"
#include <map>

using namespace std;

class SymbolList 
{
private:
	//Symbol sym;
	vector<Symbol> symbolList;

	map<string , int> symbolMap;
	map<string, bool> instrMap;

public:
	SymbolList(){
			//cout << "creating symbol list object " << endl;
	}
	
	void pushList(Symbol symbol)
	{
		//cout << "list is " << &(symbolList) << endl;
		//cout << "pushing to symbol list " << symbol.getToken() << " " << symbolList.size() << endl;
				
		if(symbolMap.count(symbol.getToken()) > 0)
		{
			int pos = symbolMap[symbol.getToken()];			
			symbolList.at(pos).setMultDef(true);
		}
		else
		{
			symbolMap.insert(pair<string, int>(symbol.getToken(), symbolList.size()));
			symbol.setMultDef(false);
			symbolList.push_back(symbol);
		}
		//cout << symbolList.size() << " at the end of push list " << endl;
	}
	
	void  printList()
	{
		vector<Symbol>::iterator it;
		cout << "Symbol Table " << endl; 
		//cout << symbolList.size() << " this is the size " << endl;
		for(it = symbolList.begin(); it != symbolList.end(); it++)
		{
			//cout << " inside printing symmol list  " << endl;
			if(it->getMultDef())
			{
				cout<< it->getToken() << "=" << it->getAbsAddr()  <<  " Error: This variable is multiple times defined; first value used" << endl;				
			}
			else
			{
			cout << it->getToken() << "=" << it->getAbsAddr() << endl;	
			}		
			
		}
	}
	
	void checkDef(int modCount, int progCount)
	{
	//	int newModCount = 0;
		vector<Symbol>:: iterator it;
			for (it = symbolList.begin(); it != symbolList.end(); it++)
			{
				if (it->getModCount() == modCount)
				{
					if(it->getRelAddr() > progCount)
					{
						cout <<endl << "Warning: Module "<<modCount << ": " << it->getToken()  <<" to big " << it->getRelAddr() << " (max="<<(progCount-1) <<") assume zero relative" << endl;
						it->setRelAddr(0);
						it->setAbsAddr(it->getModAddr() + it->getRelAddr());
					}
				}
			}
			
	}
	
	bool isSymbolPresent(string symbol)
	{
		//cout << "checking usage for symbol " << symbol << endl;
		if(symbolMap.count(symbol) > 0){
			symbolList.at(symbolMap[symbol]).setUsed(true);
			//cout << "used" << endl;
			return true;
		}
		return false;
	}
	
	void isDef()
	{
		for(vector<Symbol>::iterator it = symbolList.begin() ; it != symbolList.end(); ++it)
		{
			if (!(it->getIsUsed()))
			{
				cout << endl << "Warning: Module " << it->getModCount() << ": " << it->getToken() << " was defined but never used" << endl;
			}
		}
	}
	
	int getAbAddr(string symbol)
	{
		int i = symbolMap[symbol];
		Symbol newSymbol = symbolList.at(i);
		int absAddr = newSymbol.getAbsAddr();
		return absAddr;
	}
};
