

//
// Program Name: chatterbot4
// Description: the goal of the current version of this program is to extend the previous chatterbot,
// actualy to make it more flexible in the way it treats the inputs from the different users.
// Also this version will try controling repetions that are made by the user.
//
// Author: Gonzales Cenelia
//

#pragma warning(disable: 4786)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

const int MAX_RESP = 3;
const std::string delim = "?!.;,";

typedef std::vector vstring;

vstring find_match( std::string input );
void copy( char *array[], vstring &v );
void preprocess_input( std::string &str );
void UpperCase( std::string &str );
void cleanString( std::string &str );
bool isPunc(char c);

typedef struct {
	char *input;
	char *responses[MAX_RESP];
}record;

record KnowledgeBase[] = {
	{"WHAT IS YOUR NAME", 
	{"MY NAME IS CHATTERBOT3.",
	 "YOU CAN CALL ME CHATTERBOT3.",
	 "WHY DO YOU WANT TO KNOW MY NAME?"}
	},

	{"HI", 
	{"HI THERE!",
	 "HOW ARE YOU?",
	 "HI!"}
	},
	
	{"HOW ARE YOU",
	{"I'M DOING FINE!",
	"I'M DOING WELL AND YOU?",
	"WHY DO YOU WANT TO KNOW HOW AM I DOING?"}
	},

	{"WHO ARE YOU",
	{"I'M AN A.I PROGRAM.",
	 "I THINK THAT YOU KNOW WHO I'M.",
	 "WHY ARE YOU ASKING?"}
	},

	{"ARE YOU INTELLIGENT",
	{"YES,OFCORSE.",
	 "WHAT DO YOU THINK?",
	 "ACTUALY,I'M VERY INTELLIENT!"}
	},

	{"ARE YOU REAL",
	{"DOES THAT QUESTION REALLY MATERS TO YOU?",
	 "WHAT DO YOU MEAN BY THAT?",
	 "I'M AS REAL AS I CAN BE."}
	}
};

size_t nKnowledgeBaseSize = sizeof(KnowledgeBase)/sizeof(KnowledgeBase[0]);


int main()
{
	srand((unsigned) time(NULL));

	std::string sInput = "";
	std::string sResponse = "";
	std::string sPreviousResponse = "";
	std::string sPreviousInput = "";

	while(1) 
	{
		std::cout << ">";
		sPreviousResponse = sResponse;
		sPreviousInput = sInput;
		std::getline(std::cin, sInput);
		preprocess_input(sInput);
		vstring responses = find_match(sInput);

		if ( sInput == sPreviousInput && sInput.length() > 0 ) 
		{
			// controling repetitions made by the user
			std::cout << "YOU ARE REPEATING YOURSELF." << std::endl;
		}
		else if ( sInput == "BYE" ) 
		{
			std::cout << "IT WAS NICE TALKING TO YOU USER, SEE YOU NEXT TIME!" << std::endl;
			break;
		} 
		else if ( responses.size() == 0 ) 
		{
			// handles the case when the program doesn't understand what the user is talking about			
			std::cout << "I'M NOT SURE IF I UNDERSTAND WHAT YOU ARE TALKING ABOUT." << std::endl;
		} 
		else 
		{
			int nSelection = rand() % responses.size();
			sResponse = responses[nSelection];

			// avoids repeating the same response
			if(sResponse == sPreviousResponse) 
			{
				responses.erase(responses.begin() + nSelection);
				nSelection = rand() % responses.size();
				sResponse = responses[nSelection];
			}
			std::cout << sResponse << std::endl;
		}
	}
	
	return 0;
}

void preprocess_input( std::string &str ) 
{
	cleanString(str);
	UpperCase(str);
}

// make a search for the user's input
// inside the database of the program
vstring find_match(std::string input) 
{
	vstring result;
	for(int i = 0; i < nKnowledgeBaseSize; ++i) 
	{
		std::string keyWord(KnowledgeBase[i].input);
		// there has been some improvements made in
		// here in order to make the matching process
		// a littlebit more flexible
		if( input.find(keyWord) != std::string::npos ) 
		{
			copy( KnowledgeBase[i].responses, result );
			return result;
		}
	}
	return result;
}

// here too there was some improvement and it was to make the databse less static,
// which means that the program can now easily handle a number of responses
// for the current keyword varying from 0 to 3 responses
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
		if(str[i] == ' ' && prevChar == ' ') 
		{
			continue;
		}

		else if(!isPunc(str[i])) 
		{
			temp += str[i];
		}

		prevChar = str[i];
	}
	str = temp;
}

