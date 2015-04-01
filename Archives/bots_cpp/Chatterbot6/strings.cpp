#include "strings.h"

const std::string delim = "?!.;,*";

// convert a string to uppercase
void UpperCase( std::string &str ) 
{
	int len = str.length();

	for( int i = 0; i < len; i++ ) 
	{
		if ( str[i] >= 'a' && str[i] <= 'z' ) 
		{
			str[i] -= 'a' - 'A';
		}
	}
}

// verifies that a given 
// character is a puntuation
bool isPunc(char c) 
{
	return delim.find(c) != std::string::npos;
}

// removes punctuation and redundant
// spaces from the user's input
void cleanString( std::string &str ) 
{
	int len = str.length();
	std::string temp = "";

	char prevChar = 0;

	for(int i = 0; i < len; ++i) 
	{
		if( (str[i] == ' ' && prevChar != ' ') || !isPunc(str[i]) ) 
		{
			temp += str[i];
			prevChar = str[i];
		}	
		else if(prevChar != ' ' && isPunc(str[i]))
		{
			temp += ' ';
		}
	}
	str = temp;
}

// copie the content of a string array to a vector
void copy(char *array[], vstring &v) 
{
	for(int i = 0; i < MAX_RESP; ++i) 
	{
		if(array[i] != NULL) 
		{
			v.push_back(array[i]);
		} 
		else 
		{
			break;
		}
	}
}