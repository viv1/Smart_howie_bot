#ifndef __STRING_H__
#define __STRING_H__

#pragma warning(disable: 4786)
#include <string>
#include <vector>

const int MAX_INP = 4;
const int MAX_RESP = 6;

typedef std::vector<std::string> vstring;


bool isPunc(char c);
void cleanString( std::string &str );
void UpperCase( std::string &str );
void copy(char *array[], vstring &v, size_t array_size);

template<typename T>
void shuffle(T &array, size_t size) {
	for(int i = 0; i < size; ++i) {
		int index = rand() % size;
		std::swap(array[i], array[index]);
	}
}

#endif