//
// Program Name: Chatterbot13
// With this version of the program, we've finally made a separation between the source code of the chatbot
// and his database of keywords. So, now the database is not hard coded into the program.
//
// Author: Gonzales Cenelia
//

#include "chatterbot13.h"


transpos_t transposList[] = {
	{" MYSELF ", " YOURSELF "},
	{" DREAMS ", " DREAM "},
	{" WEREN'T ", " WASN'T "},	
	{" AREN'T ", " AM NOT "},
	{" I'VE ", " YOU'VE "},
	{" MINE ", " YOURS "},
	{" MY ", " YOUR "},
	{" WERE ", " WAS "},
	{" MOM ", " MOTHER "},
	{" I AM ", " YOU ARE "},
	{" I'M ", " YOU'RE "},
	{" DAD ", " FATHER "},
	{" MY ", " YOUR "},
	{" AM ", " ARE "},
	{" I'D ", " YOU'D "},
	{" I ", " YOU "},
	{" ME ", " YOU "}
};

size_t transposListSize = sizeof(transposList) / sizeof(transposList[0]);


void CBot::loadDatabase()
{
	std::fstream fin("script.txt", std::ios::in);
	if(fin.fail())
	{
		throw std::string("Unable to load the database: script.txt");
	}

	CResponse respObj;
	std::vector<CResponse> ListOfRespObj;
	
	std::string buffer;
	vstring keyList;

	while(std::getline(fin, buffer))
	{
		char cSymbol = buffer[0];
		buffer.erase(0, 1);
		switch(cSymbol)
		{
		case 'K':
			keyList.push_back(buffer);
			break;
		case 'C':
			respObj.addContext(buffer);
			break;
		case 'R':
			respObj.addResp(buffer);
			break;
		case '%':
			ListOfRespObj.push_back(respObj);
			respObj.clear();
			break;
		case '#':
			{
				if(ListOfRespObj.empty())
				{
					ListOfRespObj.push_back(respObj);
				}

				vstring::const_iterator iter = keyList.begin();
				for( ; iter != keyList.end(); ++iter )
				{
					KnowledgeBase[*iter] = ListOfRespObj;
				}
				keyList.clear();
				ListOfRespObj.clear();
				respObj.clear();
			}
			break;
		}
	}
	fin.close();
}

void CBot::signon()
{
	handle_event("SIGNON**");
	select_response();
	//speak(m_sResponse);
	print_response();
}

void CBot::get_input() 
{
	std::cout << ">";

	// saves the previous input
	save_prev_input();
	std::getline(std::cin, m_sInput);
}

void CBot::preprocess_input() 
{
	cleanString(m_sInput);
	trimRight(m_sInput, ". ");
	UpperCase(m_sInput);
}

void CBot::preprocess_response()
{
	if(m_sResponse.find("*") != std::string::npos)
	{
		// extracting from input
		find_subject(); 
		// conjugating subject
		transpose(m_sSubject); 

		replace(m_sResponse, "*", " " + m_sSubject);
	}
}

void CBot::extractRespList(std::vector<CResponse> objList)
{
	std::vector<CResponse>::const_iterator iter = objList.begin();
	for( ; iter != objList.end(); ++iter )
	{
		vstring ListOfContext = iter->getContextList();
		if(ListOfContext.empty())
		{
			ListOfResponse = iter->getRespList();
		}
		else if(std::find(ListOfContext.begin(), 
			ListOfContext.end(), m_sPrevResponse) != ListOfContext.end())
		{
			ListOfResponse = iter->getRespList();
			break;
		}
	}
}

void CBot::find_subject()
{
	m_sSubject.erase(); // resets subject variable
	trimRight(m_sInput, " ");
	trimLR(m_sKeyWord, "_");
	size_t pos = m_sInput.find(m_sKeyWord);
	if(pos != std::string::npos)
	{
		m_sSubject = m_sInput.substr(pos + m_sKeyWord.length() + 1, m_sInput.length() - 1);		
	}
}

bool CBot::user_repeat() const 
{
	return (m_sPrevInput.length() > 0 &&
		((m_sInput == m_sPrevInput) || (m_sInput.find(m_sPrevInput) != std::string::npos) ||
		(m_sPrevInput.find(m_sInput) != std::string::npos)));
}

bool CBot::similar_input() const 
{
	return (m_sInput.length() > 0 && (m_sInput.find(m_sPrevInput) != std::string::npos ||
			m_sPrevInput.find(m_sInput) != std::string::npos));
}

std::string CBot::get_sub_phrase(vstring wordList, size_t start, size_t end_pos)
{
	std::string buffer;
	for(int i = start; i < end_pos; ++i)
	{
		buffer += wordList[i];
		if(i != end_pos - 1)
		{
			buffer += " ";
		}
	}
	return buffer;
}

void CBot::preProcessKeyWord(std::string &str, size_t start_pos, size_t end_pos, size_t iSize)
{
	if(start_pos == 0)
	{
		str.insert(0, "_");
	}
	if(end_pos == iSize - 1)
	{
		str.insert(str.length(), "_");
	}
}

// implementing the 'sentence transposition' feature
void CBot::transpose(std::string &str)
{
	std::string buffer = " " + str + " ";
	bool bTransposed = 0;

	for(int i = 0; i < transposListSize; ++i)
	{
		std::string first = transposList[i].first;
		std::string second = transposList[i].second;

		while(replace(buffer, first, second) != std::string::npos)
		{
			bTransposed = 1;
		}
	}

	if( !bTransposed )
	{
		for( i = 0; i < transposListSize; ++i )
		{
			std::string first = transposList[i].first;
			std::string second = transposList[i].second;
			while(replace(buffer, second, first) != std::string::npos) ;
		}
	}
	trimLR(buffer, " ");
	str = buffer;
}

/// make a search for the user's input
// inside the database of the program
void CBot::find_match() 
{
	//std::fstream outfile("keywords.txt", std::ios::out);
	ListOfResponse.clear();
	
	// introduce thse new "string variable" to help 
	// support the implementation of keyword ranking 
	// during the matching process
	std::string bestKeyWord;
	vstring ListOfWord;

	if(m_sInput.find("**") == std::string::npos)
	{
		trimRight(m_sInput, ".");
		UpperCase(m_sInput);
		tokenize(m_sInput, ListOfWord);
		bestKeyWord = findBestKey(ListOfWord);
		m_sKeyWord = bestKeyWord;
	}
	else
	{
		m_sKeyWord = m_sInput;
	}
	if(KnowledgeBase.find(m_sKeyWord) != KnowledgeBase.end())
	{
		std::vector<CResponse> ListOfRespObj = KnowledgeBase[m_sKeyWord];
		extractRespList(ListOfRespObj);
	}
}

std::string CBot::findBestKey(vstring v)
{
	std::string buffer;
	int iSize = v.size();
	bool bKeyFound = 0;
	for( int i = 0, j = iSize; i < iSize && j >= 1; ++i, --j )
	{
		for( int k = 0; (k + j) <= iSize; ++k )
		{
			buffer = get_sub_phrase(v, k, k + j);
			if(KnowledgeBase.find(buffer) != KnowledgeBase.end())
			{
				bKeyFound = 1;
			}
			else
			{
				preProcessKeyWord(buffer, k, k + j, iSize);
				if(KnowledgeBase.find(buffer) != KnowledgeBase.end())
				{
					bKeyFound = 1;
				}
			}
			if(bKeyFound)
			{
				return buffer;
			}
		}
	}
	return buffer;
}

void CBot::select_response() 
{
	shuffle(ListOfResponse, ListOfResponse.size());
	m_sResponse = ListOfResponse[0];
}

void CBot::respond() 
{
	save_prev_response();
	set_event("BOT UNDERSTAND**");

	if(null_input())
	{
		handle_event("NULL INPUT**");
	}
	else if(null_input_repetition())
	{
		handle_event("NULL INPUT REPETITION**");
	}
	else if(user_repeat())
	{
		handle_user_repetition();
	}
	else
	{
		find_match();
	}
	
	if(user_want_to_quit())
	{
		m_bQuitProgram = 1;
	}

	if(!bot_understand())
	{
		handle_event("BOT DON'T UNDERSTAND**");
	}
	
	if(ListOfResponse.size() > 0)
	{
		select_response();
		preprocess_response();

		if(bot_repeat())
		{
			handle_repetition();
		}
		print_response();
		//speak(m_sResponse);
	}
}

void CBot::Initialize_TTS_Engine()
{
	if(FAILED(::CoInitialize(NULL)))
	{
		throw std::string("Unable to initialise COM objects");
	}

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&m_pVoice);

	if(FAILED(hr))
	{
		throw std::string("Unable to initialize voice engine");
	}

	m_bTTSEngineInitialised = 1;
}

void CBot::Release_TTS_Engine()
{
	if(m_bTTSEngineInitialised)
	{
		m_pVoice->Release();
		m_pVoice = NULL;
		::CoUninitialize();
	}
}

void CBot::speak(const std::string text)
{
	if(m_bTTSEngineInitialised)
	{
		WCHAR *buffer = new WCHAR[text.length() + 1];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text.c_str(), -1, buffer, text.length() + 1);
		m_pVoice->SetRate(-1);
		m_pVoice->Speak(buffer, SPF_DEFAULT, NULL);
		delete [] buffer;
	}
}

void CBot::handle_repetition()
{
	if(ListOfResponse.size() > 0)
	{
		ListOfResponse.erase(ListOfResponse.begin());
	}
	if(no_response())
	{
		save_input();
		set_input(m_sEvent);

		find_match();
		restore_input();
	}
	select_response();
}

void CBot::handle_user_repetition()
{
	if(same_input()) 
	{
		handle_event("REPETITION T1**");
	}
	else if(similar_input())
	{
		handle_event("REPETITION T2**");
	}
}

void CBot::handle_event(std::string str)
{
	save_prev_event();
	set_event(str);

	save_input();

	set_input(str);

	if(!same_event()) 
	{
		find_match();
	}

	restore_input();
}

int main()
{
	std::cout << "Chatterbot v13.0 Copyright (C) 2010 Gonzales Cenelia\n" << std::endl;
	try 
	{
		CBot bot("Chatterbot13");

		bot.signon();
		while(!bot.quit()) 
		{
			bot.get_input();
			bot.respond();
		}
	}
	catch(std::string str)
	{
		std::cerr << str << std::endl;
	}
	catch(...)
	{
		std::cerr << "The program has stop due to some unknown exception" << std::endl;
	}
		
	return 0;
}

