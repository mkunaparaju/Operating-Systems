#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Token.h"
#include <string.h>
#include "Symbol.cpp"

using namespace std;

class ReaderUtil 
{
private:

	fstream* fin;
	long fileSize;

public:

	int lineNumber;
	int columnNumber;

	ReaderUtil(fstream* in, long fSize) {
		this->fin = in;
		this->fileSize = fSize;
		lineNumber = 1;
		columnNumber = 1;
	}	


	Token<char*> nextToken() {
		char c;
		int length = 0;
		int position = 0, tokenStartLine = lineNumber, tokenStartColumn = columnNumber;
		char* token = new char[32];
		bool tokenStart = false, isWhiteSpace = false, emptyLine = true;

		//cout << "starting to read file " << endl;
		
		while(*(this->fin) >> c) {
			//cout << "character is " << c;
			if (c == '\n') {
				if (this->fin->tellg() != this->fileSize) {
					lineNumber++;
					columnNumber = 1;
				}
				emptyLine = true;
			}
			else {
				emptyLine = false;
				columnNumber++;
			}

			//cout << "Read character " << c << endl;
			
			isWhiteSpace = (c == ' ' || c == '\n' || c == '\t');

			if (tokenStart && isWhiteSpace) {
				token[position] = '\0';
				break;
			}
			else if (isWhiteSpace) {
				tokenStartLine = lineNumber;
				tokenStartColumn = columnNumber;
				continue;
			}
			else if (!tokenStart) { // token is beginning here
				tokenStartLine = lineNumber;
				tokenStartColumn = columnNumber - 1;
				tokenStart = true;
				length = 0;
			}		

			length++;
			token[position++] = c;
		}
		//cout << token << endl;
		Token<char*> newToken(tokenStartLine, tokenStartColumn, token, length);
		return newToken;
	}
	
	
	Token<int> getInteger(bool isDefList)
	{
		
		Token<char*> tok = nextToken();
		int length = tok.getLength();
		char* str = tok.getValue();
		int tokenStartLine = tok.getLineNumber();
		int tokenStartColumn = tok.getColumnNumber();
		
		//cout << "in getInteger " << str << endl;
	

		char *endptr = 0;
		
		
		//cout << "in getInteger " << str ;
		//cout << "Token start is " << tokenStartLine << " " << tokenStartColumn << endl;
		
		if((!isDefList) && (length == 0))
			//means that you are out definition list then str cannot be zero
		{
			//cout << " first num expected" << isDefList << " " << length << endl;
			cout << "Parse Error Line at line " << tokenStartLine << "offset" << tokenStartColumn << " NUM_EXPECTED " << endl;
			exit(99);
		}
	
		int count  = (int)strtol(str, &endptr,10);//count should be +ve
		//cout << "count is inside the getinteger function near endptr " << count << endl;
		if(*endptr != '\0' || count < 0)
		{
			cout << " endptr " << endptr << " count  " << count ;
			cout << " Parse Error Line " << tokenStartLine	<< " offset " << tokenStartColumn << " : NUM_EXPECTED " << endl;
			exit(99);	
		}
		
		
		 Token<int> newCountToken(tokenStartLine, tokenStartColumn, count, length);
		 return newCountToken;
		
	}
	
	Symbol getSymbol()
	{
		//check for error conditions of string length being less than zero and more than 16
		Token<char*> tok = nextToken();
		int length = tok.getLength();
		char* str = tok.getValue();
		char c = *(str+0);
		int tokenStartLine = tok.getLineNumber();
		int tokenStartColumn = tok.getColumnNumber();
		
		//cout << " in getSymbol " << str;
		if (length == 0)
		{
			cout << " parse error line " << tokenStartLine << " offset" << tokenStartColumn << " SYMBOL_EXPECTED" << endl;
			exit(99);
		}
		if 	(length > 16)
		{
			cout << " parse error line " << tokenStartLine << " offset " << tokenStartColumn << "SYM_TOLONG " << endl;
			exit(99);
		}
		
		if(c >= 48 && c < 57)
		{
			cout << " parse error line " << tokenStartLine << " offset " << tokenStartColumn << " SYMBOL_EXPECTED " << endl;
			exit(99);
		}
		
		return Symbol(tok);
	}
	
	char getAddr()
	{
		Token<char*> tok = nextToken();
		int length = tok.getLength();
		char* str = tok.getValue();
		char c = *(str+0);
		int tokenStartLine = tok.getLineNumber();
		int tokenStartColumn = tok.getColumnNumber();
		char addr = ('A'||'I'||'E'||'R');
		if (c != addr)
		{
			cout << " parse error line " << tokenStartLine << " offset " << tokenStartColumn << " ADDR_EXPECTED " << endl;
			exit(99);
		}
		
		return c;
	}
};
