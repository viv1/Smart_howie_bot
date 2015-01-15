//
// Description: This is the interface for chatterbot16
//
// Author: Gonzales Cenelia
//
#ifndef __CHATTERBOT16_H__
#define __CHATTERBOT16_H__

#include "strings.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <ctime>
#include <sapi.h>
#include <map>

class CResponse;

typedef std::map<std::string, std::vector<CResponse> > mapString;

typedef struct {
	char *first;
	char *second;
} transpos_t;



class CBot {
	
public:
	CBot (std::string str) 
		:m_sBotName(str), m_bQuitProgram(0), m_sInput("null"), m_bTTSEngineInitialised(0), m_pVoice(NULL)
	{ 
		seed_random_generator();
		Initialize_TTS_Engine();
		loadDatabase();
	}
	~CBot () {
		Release_TTS_Engine();
	};

	void get_input();
	void respond();

	void speak(const std::string text);

	void signon();

	
	bool quit() const {
		return m_bQuitProgram;
	}

	void find_match();
	void handle_repetition();
	void handle_user_repetition();
	void handle_event(std::string str);

	void seed_random_generator() {
		srand((unsigned) time(NULL));
	}

	void select_response();

	void save_prev_input() {
		m_sPrevInput = m_sInput;
	}

	void save_prev_response() {
		m_sPrevResponse = m_sResponse;
	}

	void save_prev_event() {
		m_sPrevEvent = m_sEvent;
	}

	void set_event(std::string str) {
		m_sEvent = str;
	}

	void save_input() {
		m_sInputBackup = m_sInput;
	}

	void set_input(std::string str) {
		m_sInput = str;
	}
	
	void restore_input() {
		m_sInput = m_sInputBackup;
	}
	
	void print_response() const {
		if(m_sResponse.length() > 0) {
			std::cout << m_sResponse << std::endl;
		}
	}
	
	void preprocess_input();

	void preprocess_response();

	void find_subject();

	bool bot_repeat();

	bool user_repeat() const;

	bool bot_understand() const {
		return ListOfResponse.size() > 0;
	}

	bool null_input() const {
		return (m_sInput.length() == 0 && m_sPrevInput.length() != 0);
	}

	bool null_input_repetition() const {
		return (m_sInput.length() == 0 && m_sPrevInput.length() == 0);
	}

	bool user_want_to_quit() const {
		return m_sInput.find("BYE") != std::string::npos;
	}

	bool same_event() const {
		return (m_sEvent.length() > 0 && m_sEvent == m_sPrevEvent);
	}

	bool no_response() const {
		return ListOfResponse.size() == 0;
	}

	bool same_input() const {
		return (m_sInput.length() > 0  && m_sInput == m_sPrevInput);
	}

	std::string get_sub_phrase(vstring wordList, size_t start, size_t end);
	std::string findBestKey(vstring v);

	void preProcessKeyWord(std::string &str, size_t start_pos, size_t end_pos, size_t iSize);

	bool similar_input() const;

	void transpose(std::string &str);

	void Initialize_TTS_Engine();
	void Release_TTS_Engine();

	void addXmlTag(std::string &str);

	void loadDatabase();
	void extractRespList(std::vector<CResponse> objList);

	void save_bot_response() {
		if(!m_sResponse.empty()) vResponseLog.push(m_sResponse);
	}

	int findRespPos(std::string str);

	void save_unknown_input();

	void update_unkown_input_list() {
		ListOfUnknownInput.push_back(m_sInput);
	}

	void save_log();
	void save_log(std::string str);

private:
	std::string			m_sBotName;
	std::string			m_sUserName;
	std::string			m_sInput;
	std::string			m_sResponse;
	std::string			m_sPrevInput;
	std::string			m_sPrevResponse;
	std::string			m_sEvent;
	std::string			m_sPrevEvent;
	std::string			m_sInputBackup;
	std::string			m_sSubject;
	std::string			m_sKeyWord;
	std::string			m_sContext;
	std::string			m_sPrevContext;
	bool				m_bQuitProgram;
	bool				m_bTTSEngineInitialised;
	ISpVoice			*m_pVoice;

	vstring						ListOfResponse;
	vstring						ListOfUnknownInput;
	std::stack<std::string>		vResponseLog;

	mapString			KnowledgeBase;

	std::fstream		logfile;
	
};


class CResponse {
public:
	CResponse() {}
	~CResponse() {}

	void addContext(std::string str) 
	{
		ListOfContext.push_back(str);
	}

	void addResp(std::string str)
	{
		ListOfResp.push_back(str);
	}

	vstring getContextList() const 
	{
		return ListOfContext;
	}

	vstring getRespList() const 
	{
		return ListOfResp;
	}

	void clear()
	{
		ListOfResp.clear();
		ListOfContext.clear();
	}

private:
	vstring ListOfContext;
	vstring ListOfResp;
};

#endif
