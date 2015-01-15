//
// Program Name: Chatterbot16
// Chatterbot introduces an algorithm to save the conversation exchange between the user and chatbot
// This could help us improve the chatterbot by the fiding the weakness of the bot during a chating session
//
// Author: Gonzales Cenelia
//

#include "chatterbot16.h"


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


void CBot::save_unknown_input()
{
	std::fstream fout("unknown.txt", std::ios::out);
	if(fout.fail())
	{
		throw std::string("Unable to save Unknown Input List");
	}
	vstring::const_iterator iter = ListOfUnknownInput.begin();
	for( ; iter != ListOfUnknownInput.end(); ++iter )
	{
		fout << *iter << std::endl;
	}
	fout.flush();
	fout.close();
}

void CBot::save_log()
{
	time_t ltime; 
	time(&ltime);
	logfile.open("log.txt", std::ios::out | std::ios::app);
	if(logfile.fail()) 
	{
		throw std::string("can't save conversation log");
	}
	logfile << "\n\nConversation log - " << ctime(&ltime) << std::endl;
}

void CBot::save_log(std::string str)
{
	if(str == "CHATTERBOT") 
	{
		logfile << m_sResponse << std::endl;
	} 
	else if(str == "USER") 
	{
		logfile << ">" << m_sInput << std::endl;
	}
}

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
	save_log();
	save_log("CHATTERBOT");
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

bool CBot::bot_repeat()
{
	int pos = findRespPos(m_sResponse);
	if(pos > 0)
	{
		return pos + 1 < ListOfResponse.size();
	}
	return 0;
}

int CBot::findRespPos(std::string str)
{
	int pos = -1;
	std::stack<std::string> s = vResponseLog;
	while(s.empty())
	{
		++pos;
		if(s.top() == str)
		{
			break;
		}
		s.pop();
	}
	return pos;
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

// make a search for the user's input
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
	if(bot_understand()) 
	{
		shuffle(ListOfResponse, ListOfResponse.size());
		m_sResponse = ListOfResponse[0];
	}
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
		update_unkown_input_list();
	}
	
	if(ListOfResponse.size() > 0)
	{
		select_response();
		save_bot_response();
		preprocess_response();

		if(bot_repeat())
		{
			handle_repetition();
		}
		save_log("CHATTERBOT");
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
	std::map<int, std::string> ListOfPrevResponse;
	if(ListOfResponse.size() > 1)
	{
		std::stack<std::string> s = vResponseLog;
		vstring::const_iterator iter = ListOfResponse.begin();
		for( ; iter != ListOfResponse.end(); ++iter )
		{
			int pos = findRespPos(*iter);
			ListOfPrevResponse[pos] = *iter;
		}
	}
	std::map<int, std::string>::const_iterator iter2 = ListOfPrevResponse.end();
	--iter2;
	m_sResponse = iter2->second;
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
	std::cout << "Chatterbot v16.0 Copyright (C) 2010 Gonzales Cenelia\n" << std::endl;
	try 
	{
		CBot bot("Chatterbot16");

		bot.signon();
		while(!bot.quit()) 
		{
			bot.get_input();
			bot.save_log("USER");
			bot.respond();
		}
		bot.save_unknown_input();
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

