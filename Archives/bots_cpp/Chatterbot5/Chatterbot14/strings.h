#ifndef __STRING_H__
#define __STRING_H__

#pragma warning(disable: 4786)
#pragma warning(disable: 4503)
#include <string>
#include <vector>

const int MAX_INP = 5;
const int MAX_RESP = 7;

typedef std::vector<std::string> vstring;


bool isPunc( char c );
void cleanString( std::string &str );
void UpperCase( std::string &str );
void trimLeft(std::string &str, std::string delim);
void trimRight( std::string &str, std::string delim );
void trimLR(std::string &str, std::string characters);
void copy( char *array[], vstring &v, size_t array_size );
size_t replace( std::string &str, std::string substr1, std::string substr2 );
void tokenize(const std::string str, vstring &v);

template<typename T>
void shuffle( T &array, size_t size ) 
{
	for( int i = 0; i < size; ++i ) 
	{
		int index = rand() % size;
		std::swap(array[i], array[index]);
	}
}

#endif