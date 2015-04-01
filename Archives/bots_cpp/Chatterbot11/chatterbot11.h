//
// Description: This is the interface for chatterbot11
//
// Author: Gonzales Cenelia
//
#ifndef __CHATTERBOT11_H__
#define __CHATTERBOT11_H__

#include "strings.h"
#include <iostream>
#include <ctime>


typedef struct {
	char *keyword[MAX_INP];
	char *response[MAX_RESP];
	char *context[MAX_RESP];
} record;

typedef struct {
	char *first;
	char *second;
} transpos_t;


class CBot {
	
public:
	CBot (std::string str) 
		:m_sBotName(str), m_bQuitProgram(0), m_sInput("null")
	{ 
		seed_random_generator();
	}
	~CBot () {};

	void get_input();
	void respond();

	void signon();

	
	bool quit() const {
		return m_bQuitProgram;
	}

private:
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

	bool bot_repeat() const {
		return (m_sPrevResponse.length() > 0 && 
			m_sResponse == m_sPrevResponse);
	}

	bool user_repeat() const;

	bool bot_understand() const {
		return response_list.size() > 0;
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
		return response_list.size() == 0;
	}

	bool same_input() const {
		return (m_sInput.length() > 0  && m_sInput == m_sPrevInput);
	}

	bool wrong_location(std::string keyword, char firstChar, char lastChar, size_t pos);
	bool wrong_context(vstring context_list);

	bool similar_input() const;

	void transpose(std::string &str);

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

	vstring				response_list;
	
};

#endif
