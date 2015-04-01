#include "strings.h"

const std::string delim = "?!;,";

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
			prevChar = ' ';
		}
	}
	str = temp;
}

// copy the content of a string array to a vector
void copy(char *array[], vstring &v, size_t array_size) 
{
	for(int i = 0; i < array_size; ++i) 
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

size_t replace(std::string &str, std::string substr1, std::string substr2) {
	size_t pos = str.find(substr1);
	if(pos != std::string::npos) {
		str.erase(pos, substr1.length());
		str.insert(pos, substr2);
	}
	return pos;
}

void trimRight(std::string &str, std::string delim) {
	size_t pos = str.find_last_not_of(delim);
	if(pos != std::string::npos) {
		str.erase(pos + 1, str.length());
	}
}

void trimLeft(std::string &str, std::string delim) {
	size_t pos = str.find_first_not_of(delim);
	if(pos != std::string::npos) {
		str.erase(0, pos);
	}
}

// trim all left and right characters that is specified by
// the string "characters"
void trimLR(std::string &str, std::string characters) {
	trimLeft(str, characters);
	trimRight(str, characters);
}

void tokenize(const std::string str, vstring &v) {
	std::string buffer;
	for(int i = 0; i < str.length(); ++i) {
		if(!isPunc(str[i]) && !isspace(str[i]) && str[i] != '.') {
			buffer += str[i];
		} else if(!buffer.empty()) {
			v.push_back(buffer);
			buffer.erase();
		}
	}
	if((v.empty() && !buffer.empty()) || !buffer.empty()) {
		v.push_back(buffer);
	}
}
