
#include <list>
#include <string>
#include "Token.h"

using namespace std;

class SymbolList 
{
private:
	//Symbol sym;
	list<Symbol> symbolList;


public:
	void pushList(Symbol symbol)
	{
		symbolList.push_front(symbol);
	}
	
	void  printList(SymbolList sl)
	{
		
	}

};