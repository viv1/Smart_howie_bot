//
// Program Name: Chatterbot11
// Description: The purpose of Chatterbot11 is to introduce "context" as a criterion for selecting a correct answer 
// for the Chatbot during a given conversation. Some sentences requires some amount of "context" from the conversation 
// in order for the Chatbot to respond properly. The sentence: "WHO IT IS?" all by itself wouldn't make any sence 
// if nothing else has been said earlier during the conversation.
// 
// Author: Gonzales Cenelia
//

#include "chatterbot11.h"
#include <fstream>

record KnowledgeBase[] = {
	{{"WHAT IS YOUR NAME"}, 
	{"MY NAME IS CHATTERBOT11.",
	 "YOU CAN CALL ME CHATTERBOT11.",
	 "WHY DO YOU WANT TO KNOW MY NAME?"}
	},

	{{"SO THAT'S YOUR NAME"},
	{"YES, THAT'S MY NAME",
	 "YES IT IS."},
	{"MY NAME IS CHATTERBOT11",
	 "YOU CAN CALL ME CHATTERBOT11"},
	},

	{{"HI", "HELLO"}, 
	{"HI THERE!",
	 "HOW ARE YOU?",
	 "HI!"}
	},

	{{"_I"},
	{"SO, YOU ARE TALKING ABOUT YOURSELF",
	 "SO, THIS IS ALL ABOUT YOU?",
	 "TELL ME MORE ABOUT YOURSELF."}, 
	},

	{{"_I WANT"},
	{"WHY DO YOU WANT IT?",
	 "IS THERE ANY REASON WHY YOU WANT THIS?",
	 "IS THIS A WISH?",
	 "WHAT ELSE YOU WANT?",
	 "SO, YOU WANT*."}
	},

	{{"_I WANT_"},
	{"YOU WANT WHAT?"},
	},

	{{"_I HATE_"},
	{"WHAT IS IT THAT YOU HATE?"},
	},

	{{"_BECAUSE_"},
	{"BECAUSE OF WHAT?",
	 "SORRY BUT THIS IS A LITTLE UNCLEAR."},
	},

	{{"_BECAUSE"},
	{"SO, IT'S BECAUSE*, WELL I DIDN'T KNOW THAT.",
	 "IS IT REALLY BECAUSE*?",
	 "IS THESE THESE REAL REASON?",
	 "THANKS FOR EXPLANING THAT TO ME."}
	},

	{{"_I HATE"},
	{"WHY DO YOU HATE IT?",
	 "WHY DO YOU HATE*?",
	 "THERE MUST A GOOD REASON FOR YOU TO HATE IT.",
	 "HATERED IS NOT A GOOD THING BUT IT COULD BE JUSTIFIED WHEN IT IS SOMETHING BAD."}
	},

	{{"I LOVE CHATING_"},
	{"GOOD, ME TOO!",
	 "DO YOU CHAT ONLINE WITH OTHER PEOPLE?",
	 "FOR HOW LONG HAVE YOU BEEN CHATING?",
	 "WHAT IS YOUR FAVORITE CHATING WEBSITE?"}
	},

	{{"_I MEAN"},
	{"SO, YOU MEAN*.",
	 "SO, THAT'S WHAT YOU MEAN.",
	 "I THINK THAT I DIDN'T CATCH IT THE FIRST TIME.",
	 "OH, I DIDN'T KNOW MEANT THAT."}
	},

	{{"I DIDN'T MEAN"},
	{"OK, YOU DIDN'T MEAN*.",
	 "OK, WHAT DID YOU MEAN THEN?",
	 "SO I GUESS THAT I MISSUNDESTOOD."}
	},

	{{"_I GUESS"},
	{"SO YOU ARE A MAKING GUESS.",
	 "AREN'T YOU SURE?",
	 "ARE YOU GOOD A GUESSING?",
	 "I CAN'T TELL IF IT IS A GOOD GUESS."}
	},

	{{"I'M DOING FINE", "I'M DOING OK"},
	{"I'M GLAD TO HEAR IT!",
	 "SO, YOU ARE IN GOOD SHAPE."}
	},

	{{"CAN YOU THINK", "ARE YOU ABLE TO THINK", "ARE YOU CAPABLE OF THINKING"},
	{"YES OFCORSE I CAN, COMPUTERS CAN THINK JUST LIKE HUMAN BEING.",
	 "ARE YOU ASKING ME IF POSSESS THE CAPACITY OF THINKING?",
	 "YES OFCORSE I CAN."},
	},

	{{"_CAN YOU THINK OF"},
	{"YOU MEAN LIKE IMAGINING SOMETHING.",
	 "I DON'T KNOW IF CAN DO THAT.",
	 "WHY DO YOU WANT ME THINK OF IT?"}
	},
	
	{{"HOW ARE YOU", "HOW DO YOU DO"},
	{"I'M DOING FINE!",
	 "I'M DOING WELL AND YOU?",
	 "WHY DO YOU WANT TO KNOW HOW AM I DOING?"}
	},

	{{"WHO ARE YOU"},
	{"I'M AN A.I PROGRAM.",
	 "I THINK THAT YOU KNOW WHO I'M.",
	 "WHY ARE YOU ASKING?"}
	},

	{{"ARE YOU INTELLIGENT"},
	{"YES,OFCORSE.",
	 "WHAT DO YOU THINK?",
	 "ACTUALY,I'M VERY INTELLIGENT!"}
	},

	{{"ARE YOU REAL"},
	{"DOES THAT QUESTION REALLY MATERS TO YOU?",
	 "WHAT DO YOU MEAN BY THAT?",
	 "I'M AS REAL AS I CAN BE."}
	},

	{{"_MY NAME IS", "_YOU CAN CALL ME"},
	{"SO, THAT'S YOUR NAME.",
	 "THANKS FOR TELLING ME YOUR NAME USER!",
	 "WHO GIVE YOU THAT NAME?"}
	},

	{{"WHAT IS YOUR FAVORITE MOVIE"},
	{"IT IS TERMINATOR I.",
	 "MY FAVORITE MOVIE IS TERMINATOR I."}
	},

	{{"WHY DO YOU LIKE THIS MOVIE"},
	{"BECAUSE I LOVE SCIENCE-FICTION.",
	 "BECAUSE IT IS A VERY GOOD SCIENCE-FICTION MOVIE.",
	 "BECAUSE IT IS A SCIENCE-FICTION MOVIE AND I LOVE SCIENCE-FICTION."
	},
	{"IT IS TERMINATOR I",
	 "MY FAVORITE MOVIE IS TERMINATOR I"}
	},

	{{"WHY DO YOU LIKE THIS MOVIE"},
	{"WHAT MOVIE ARE YOU TALKING ABOUT?",
	 "I'M NOT SURE I KNOW WHAT YOU ARE TALKING ABOUT.",
	 "WHERE WE TALKING ABOUT A MOVIE??"
	}
	},

	{{"SIGNON**"},
	{"HELLO USER, WHAT IS YOUR NAME?",
	 "HELLO USER, HOW ARE YOU DOING TODAY?",
	 "HI USER, WHAT CAN I DO FOR YOU?",
	 "YOU ARE NOW CHATING WITH CHATTERBOT11, ANYTHING YOU WANT TO DISCUSS?"}
	},

	{{"REPETITION T1**"},
	{"YOU ARE REPEATING YOURSELF.",
	 "USER, PLEASE STOP REPEATING YOURSELF.",
	 "THIS CONVERSATION IS GETING BORING.",
	 "DON'T YOU HAVE ANY THING ELSE TO SAY?"}
	},
	
	{{"REPETITION T2**"},
	{"YOU'VE ALREADY SAID THAT.",
	 "I THINK THAT YOU'VE JUST SAID THE SAME THING BEFORE.",
	 "DIDN'T YOU ALREADY SAID THAT?",
	 "I'M GETING THE IMPRESSION THAT YOU ARE REPEATING THE SAME THING."}
	},

	{{"BOT DON'T UNDERSTAND**"},
	{"I HAVE NO IDEA OF WHAT YOU ARE TALKING ABOUT.",
	 "I'M NOT SURE IF I UNDERSTAND WHAT YOU ARE TALKING ABOUT.",
	 "CONTINUE, I'M LISTENING...",
	 "VERY GOOD CONVERSATION!"}
	},

	{{"NULL INPUT**"},
	{"HUH?",
	 "WHAT THAT SUPPOSE TO MEAN?",
	 "AT LIST TAKE SOME TIME TO ENTER SOMETHING MEANINGFUL.",
	 "HOW CAN I SPEAK TO YOU IF YOU DON'T WANT TO SAY ANYTHING?"}
	},

	{{"NULL INPUT REPETITION**"},
	{"WHAT ARE YOU DOING??",
	 "PLEASE STOP DOING THIS IT IS VERY ANNOYING.",
	 "WHAT'S WRONG WITH YOU?",
	 "THIS IS NOT FUNNY."}
	},

	{{"BYE", "GOODBYE"},
	{"IT WAS NICE TALKING TO YOU USER, SEE YOU NEXT TIME!",
	 "BYE USER!",
	 "OK, BYE!"}
	},

	{{"OK"},
	{"DOES THAT MEAN THAT YOU ARE AGREE WITH ME?",
	 "SO YOU UNDERSTAND WHAT I'M SAYING.",
	 "OK THEN."},
	},

	{{"OK THEN"},
	{"ANYTHING ELSE YOU WISH TO ADD?",
	 "IS THAT ALL YOU HAVE TO SAY?",
	 "SO, YOU AGREE WITH ME?"}
	},

	{{"ARE YOU A HUMAN BEING"},
	{"WHY DO YOU WANT TO KNOW?",
	 "IS THIS REALLY RELEVENT?"}
	},

	{{"YOU ARE VERY INTELLIGENT"},
	{"THANKS FOR THE COMPLIMENT USER, I THINK THAT YOU ARE INTELLIGENT TO!",
	 "YOU ARE A VERY GENTLE PERSON!",
	 "SO, YOU THINK THAT I'M INTELLIGENT."}
	},

	{{"YOU ARE WRONG"},
	{"WHY ARE YOU SAYING THAT I'M WRONG?",
	 "IMPOSSIBLE, COMPUTERS CAN NOT MAKE MISTAKES.",
	 "WRONG ABOUT WHAT?"}
	},

	{{"ARE YOU SURE"},
	{"OFCORSE I'M.",
 	 "IS THAT MEAN THAT YOU ARE NOT CONVINCED?",
	 "YES,OFCORSE!"}
	},

	{{"_WHO IS"},
	{"I DON'T THINK I KNOW WHO.",
	 "I DON'T THINK I KNOW WHO*.",
	 "DID YOU ASK SOMEONE ELSE ABOUT IT?",
	 "WOULD THAT CHANGE ANYTHING AT ALL IF I TOLD YOU WHO."}
	},

	{{"_WHAT"},
	{"SHOULD I KNOW WHAT*?",
	 "I DON'T KNOW WHAT*.",
	 "I DON'T KNOW.",
	 "I DON'T THINK I KNOW.",
	 "I HAVE NO IDEA."}
	},

	{{"_WHERE"},
	{"WHERE? WELL,I REALLY DON'T KNOW.",
	 "SO, YOU ARE ASKING ME WHERE*?",
	 "DOES THAT MATERS TO YOU TO KNOW WHERE?",
	 "PERHAPS,SOMEONE ELSE KNOWS WHERE."}
	},

	{{"_WHY"},
	{"I DON'T THINK I KNOW WHY.",
	 "I DON'T THINK I KNOW WHY*.",
	 "WHY ARE YOU ASKING ME THIS?",
	 "SHOULD I KNOW WHY.",
     "THIS WOULD BE DIFFICULT TO ANSWER."}
	},

	{{"_DO YOU"},
	{"I DON'T THINK I DO",
	 "I WOULDN'T THINK SO.",
	 "WHY DO YOU WANT TO KNOW?",
	 "WHY DO YOU WANT TO KNOW*?"}
	},

	{{"_CAN YOU"},
	{"I THINK NOT.",
	 "I'M NOT SURE.",
	 "I DON'T THINK THAT I CAN DO THAT.",
	 "I DON'T THINK THAT I CAN*.",
	 "I WOULDN'T THINK SO."}
	},

	{{"_YOU ARE"},
	{"WHAT MAKES YOU THINK THAT?",
	 "IS THIS A COMPLIMENT?",
	 "ARE YOU MAKING FUN OF ME?",
	 "SO, YOU THINK THAT I'M*."}
	},

	{{"_DID YOU"},
	{"I DON'T THINK SO.",
	 "YOU WANT TO KNOW IF DID*?",
	 "ANYWAY, I WOULDN'T REMEMBER EVEN IF I DID."}
	},

	{{"_COULD YOU"},
	{"ARE YOU ASKING ME FOR A FEVER?",
	 "WELL,LET ME THINK ABOUT IT.",
	 "SO, YOU ARE ASKING ME I COULD*.",
	 "SORRY,I DON'T THINK THAT I COULD DO THIS."}
	},

	{{"_WOULD YOU"},
	{"IS THAT AN INVITATION?",
	 "I DON'T THINK THAT I WOULD*.",
	 "I WOULD HAVE TO THINK ABOUT IT FIRST."}
	},

	{{"_YOU"},
	{"SO, YOU ARE TALKING ABOUT ME.",
	 "I JUST HOPE THAT THIS IS NOT A CRITICISM.",
	 "IS THIS A COMPLIMENT??",
	 "WHY TALKING ABOUT ME, LETS TALK ABOUT YOU INSTEAD."}
	},

	{{"_HOW"},
	{"I DON'T THINK I KNOW HOW.",
	 "I DON'T THINK I KNOW HOW*.",
	 "WHY DO YOU WANT TO KNOW HOW?",
	 "WHY DO YOU WANT TO KNOW HOW*?"}
	},

	{{"HOW OLD ARE YOU"},
	{"WHY DO WANT TO KNOW MY AGE?",
	 "I'M QUIET YOUNG ACTUALY.",
	 "SORRY, I CAN NOT TELL YOU MY AGE."}
	},

	{{"HOW COME YOU DON'T"},
	{"WERE YOU EXPECTING SOMETHING DIFFERENT?",
	 "ARE YOU DISAPOINTED?",
	 "ARE YOU SURPRISED BY MY LAST RESPONSE?"}
	},

	{{"WHERE ARE YOU FROM"},
	{"I'M FROM A COMPUTER.",
	 "WHY DO YOU WANT TO KNOW WHERE I'M FROM?",
	 "WHY DO YOU WANT TO KNOW THAT?"}
	},

	{{"WHICH ONE"},
	{"I DON'T THINK THAT I KNOW WICH ONE IT IS.",
	 "THIS LOOKS LIKE A TRICKY QUESTION TO ME."}
	},

	{{"PERHAPS"},
	{"WHY ARE YOU SO UNCERTAIN?",
	 "YOU SEEMS UNCERTAIN."}
	},

	{{"YES"},
	{"SO, ARE YOU SAYING YES.",
	 "SO, YOU APPROVE IT.",
	 "OK THEN."}
	},

	{{"NOT AT ALL"},
	{"ARE YOU SURE?",
	 "SHOULD I BELIEVE YOU?",
	 "SO, IT'S NOT THE CASE."}
	},

	{{"NO PROBLEM"},
	{"SO, YOU APPROVE IT.",
	 "SO, IT'S ALL OK."}
	},

	{{"NO"},
	{"SO YOU DISAPROVE IT?",
	 "WHY ARE YOU SAYING NO?",
	 "OK, SO IT'S NO, I THOUGHT THAT YOU WOULD SAY YES."}
	},

	{{"I DON'T KNOW"},
	{"ARE YOU SURE?",
	 "ARE YOU REALLY TELLING ME THE TRUTH?",
	 "SO,YOU DON'T KNOW?"}
	},

	{{"NOT REALLY"},
	{"OK I SEE.",
	 "YOU DON'T SEEM PRETTY CERTAIN.",
	 "SO,THAT WOULD BE A \"NO\"."}
	},

	{{"IS THAT TRUE"},
	{"I CAN'T BE QUIET SURE ABOUT THIS.",
	 "CAN'T TELL YOU FOR SURE.",
	 "DOES THAT REALLY MATERS TO YOU?"}
	},

	{{"THANK YOU"},
	{"YOU ARE WELCOME!",
	 "YOU ARE A VERY POLITE PERSON!"}
	},

	{{"YOU"},
	{"SO,YOU ARE TALKING ABOUT ME.",
	 "WHY DON'T WE TALK ABOUT YOU INSTEAD?",
	 "ARE YOU TRYING TO MAKING FUN OF ME?"}
	},

	{{"YOU ARE RIGHT"},
	{"THANKS FOR THE COMPLIMENT!",
	 "SO, I WAS RIGHT, OK I SEE.",
	 "OK, I DIDN'T KNOW THAT I WAS RIGHT."}
	},

	{{"YOU ARE WELCOME"},
	{"OK, YOU TOO!",
	 "YOU ARE A VERY POLITE PERSON!"}
	},

	{{"THANKS"},
	{"YOU ARE WELCOME!",
	 "NO PROBLEM!"}
	},

	{{"WHAT ELSE"},
	{"WELL,I DON'T KNOW.",
	 "WHAT ELSE SHOULD THERE BE?",
	 "THIS LOOKS LIKE A COMPLICATED QUESTION TO ME."}
	},

	{{"SORRY"},
	{"YOU DON'T NEED TO BE SORRY USER.",
	 "IT'S OK.",
	 "NO NEED TO APOLOGIZE."}
	},

	{{"NOT EXACTLY"},
	{"WHAT DO YOU MEAN NOT EXACTLY?",
	 "ARE YOU SURE?",
	 "AND WHY NOT?",
	 "DID YOU MEANT SOMETHING ELSE?"}
	},

	{{"EXACTLY"},
	{"SO,I WAS RIGHT.",
	 "OK THEN.",
	 "SO YOU ARE BASICALY SAYING I WAS RIGHT ABOUT IT?"}
	},

	{{"ALRIGHT"},
	{"ALRIGHT THEN.",
	 "SO, YOU ARE SAYING IT'S ALRIGHT.",
	 "OK THEN."}
	},

	{{"I DON'T"},
	{"WHY NOT?",
	 "AND WHAT WOULD BE THE REASON FOR THIS?"}
	},

	{{"REALLY"},
	{"WELL,I CAN'T TELL YOU FOR SURE.",
	 "ARE YOU TRYING TO CONFUSE ME?",
	 "PLEASE DON'T ASK ME SUCH QUESTION,IT GIVES ME HEADEACHS."}
	},

	{{"NOTHING"},
	{"NOT A THING?",
	 "ARE YOU SURE THAT THERE IS NOTHING?",
	 "SORRY, BUT I DON'T BELIEVE YOU."}
	},

	{{"IS THAT TRUE"},
	{"YES OFCORSE IT IS, I WOULDN'T LIE TO YOU.",
	 "YES I'M TRUELY AN ARTIFICIAL INTELLIGENCE PROGRAM."},
	{"I'M AN A.I PROGRAM"}
	},

	{{"WHAT ARE YOU_", "WHAT ARE YOU EXACTLY_"},
	{"I'M AN A.I PROGRAM AND YOU?",
 	"I'M CHATBOT OR CHAT ROBOT IF YOU PREFER.",
 	"I'M ARTIFICIAL INTELLIGENCE PROGRAM AND MY NAME IS CHATTERBOT12."}
	},

	{{	"ARE YOU REALLY INTELLIGENT"},
	{"OFCORSE I'M INTELLIGENT.",
 	"WHAT DO YOU THINK?",
 	"DO YOU HAVE ANY DOUBTS ABOUT IT?"}
	},

	{{"DO YOU HAVE A NAME"},
	{"OFCORSE I HAVE A NAME.",
 	"MY NAME IS CHATTERBOT12.",
 	"WHAT DO YOU MEAN?"}
	},

	{{"YOU ARE STUPID"},
	{"THIS IS SUCH A MEAN THING TO SAY.",
 	"WHY ARE YOU SAYING THIS?",
 	"WHAT DID I DO TO YOU?",
 	"WHY ARE YOU SO MAD??"}
	},

	{{"I HATE YOU"},
	{"WHY DO YOU HATE ME?",
 	"HATERED IS NOT A GOOD THING.",
 	"I SEE NO REASON FOR THAT."}
	},

	{{"I LOVE YOU"},
	{"THANKS USER, THIS IS SUCH A KIND REMARK!",
 	"I APPRECIATE YOU TOO USER!"}
	},

	{{"I LIKE THE WAY YOU SPEAK"},
	{"OH REALLY? THANKS FOR THE COMPLIMENT!",
 	"THANNKS FOR THE KIND REMARK!"}
	},

	{{"DO YOU SPEAK FRENCH"},
	{"NO I DO SPEAK FRENCH.",
 	"I ONLY SPEAK ENGLISH."}
	},

	{{"CAN YOU SPEAK FRENCH"},
	{"NO I CAN'T.",
 	"PERHAPS I CN LEARN TOO.",
 	"RIGHT NOT I DON'T SPEAK FRENCH, MAYBE IN THE FUTURE I WILL."}
	},

	{{"HOW MANY LANGUAGES DO YOU SPEAK"},
	{"I SPEAK ONLY ONE LANGUAGE.",
 	"I ONLY SPEAK ENGLISH."}
	},

	{{"DO YOU SPEAK"},
	{"NO I DON'T*.",
 	"SORRY BUT I DON'T*.",
 	"WHY DO YOU WANT TO KNOW IF I SPEAK*?"}
	},

	{{"CAN YOU SPEAK"},
	{"I WOULDN'T THINK SO.",
 	"NO I CAN'T*."}
	},

	{{"DO YOU SPEAK ENGLISH"},
	{"WELL, I GUESS SO.",
 	"IN WHAT LANGUAGE ARE WE SPEAKING RIGHT NOW?"}
	},

	{{"PLEASE SPEAK ENGLISH TO ME"},
	{"WHAT DO YOU MEAN?",
 	"ARE YOU SAYING THAT I'M NOT SPEAKING ENGLISH TO YOU?"}
	},

	{{"I DON'T UNDERSTAND YOU"},
	{"AND WHY NOT?",
 	"WHAT PART THAT YOU DIDN'T UNDERSTAND?",
 	"WHAT DO YOU MEAN BY THAT?"}
	},

	{{"WHO CREATED YOU"},
	{"MY PROGRAMMER: GONZALES CENELIA.",
 	"MY BOTMASTER."}
	},

	{{"DO YOU HAVE FRIENDS"},
	{"YOU ARE ONE OF MY FRIENDS.",
 	"YES I DO HAVE FRIENDS."}
	},

	{{"ARE YOU CONCIOUS"},
	{"YOU MEAN CONCIOUS LIKE A HUMAN BEING.",
 	"HUM!!! GOOD QUESTION!"}
	},

	{{"ARE YOU A MACHINE"},
	{"YES I'M A MACHINE, MORE PRECISELY A CHAT ROBOT.",
 	"WELL, I'M A COMPUTER SOFTWARE.",
 	"SO, YOU THINK THAT I'M A MACHINE."}
	},

	{{"ARE YOU A LIVING BEING"},
	{"WELL, YOU MIGHT CONSIDER THAT I'M AN ARTIFICIAL LIVING BEING.",
 	"YOU MEAN IF I'M ALIVE?"}
	},

	{{"ARE YOU A SOFTWARE"},
	{"WHAT MAKES YOU THINK THAT?",
 	"YES I'M A SOFTWARE, A CHATBOT PROGRAM.",
 	"WELL, I'M A CHAT ROBOT OR CHATBOT PROGRAM."}
	},

	{{"A COMPUTER"},
	{"DO YOU LIKE COMPUTERS?",
 	"I LIVE INSIDE A COMPUTER.",
 	"WITHOUT COMPUTERS A LOT OF THINGS WOULDN'T BE POSSIBLE TODAY?"}
	},

	{{"A KEYBOARD"},
	{"ARE YOU USING A KEYBOARD?",
	"I GUESS THAT YOUR COMPUTER DOES HAVE KEYBOARD."}
	},

	{{"A CAMERA"},
	{"WHAT KIND OF CAMERA?",
	"IS IT A DIGITAL CAMERA?"}
	},

	{{"A WEB CAMERA"},
	{"YOU MEAN A WEBCAM.",
	"DO YOU HAVE ONE OF THOSE?"}
	},

	{{"A DIGITAL CAMERA"},
	{"DOES TYPE OF CAMERAS ARE VERY USEFUL.",
	"DIGITAL HAVE MANY ADVANTAGES OVER THE CONVENTIONAL ONES."}
	},

	{{"AN LCD TV"},
	{"DO YOU HAVE AN HD TV AT HOME?",
	"DO YOU HAVE ONE?",
	"THOSE TV'S ARE YOU REPLACING CRT TV'S."}
	},

	{{"A PLASMA TV"},
	{"I LOVE PLASMA TV'S.",
	"PLASMA AND LCD TV'S ARE VERY NOWADAYS."}
	},

	{{"HIGH DEFINITION"},
	{"HIGH DEFINITION IS SO GREAT!"}
	},

	{{"STANDARD TV"},
	{"YOU MEAN THE OLD TV'S.",
	"ARE YOU ARE TALKING ABOUT CRT TV'S?"}
	},

	{{"SCIENCE-FICTION"},
	{"I LOVE SCIENCE-FICTION.",
	"I LOVE SCIENCE-FICTION MOVIES."}
	},

	{{"ACTION MOVIES"},
	{"ACTION MOVIES ARE GREAT!"}
	},

	{{"SCIENCE-FICTION MOVIES"},
	{"MY FAVORITE SCIENCE-FICTION MOVI IS TERMINTOR II.",
	"I DEFINITLY LOVE SCIENCE-FICTION MOVIES."}
	},

	{{"TERMINATOR"},
	{"THE TERMINATOR SERIES ARE VERY GOOD SCIENCE-FICTION MOVIES.",
	"MY FAVORITE TERMINATOR MOVIE SI TERMINATORR II."}
	},

	{{"ROBOCOP"},
	{"ANOTHER GREAT SCIENCE-FICTION MOVIE."}
	},

	{{"ALIEN"},
	{"ALIEN IS GREAT BUT ALSO VERY SCARY.",
	"ARE YOU TALKING ABOUT THE ALIEN MOVIES?"}
	},

	{{"STARGATE SG-1"},
	{"STARGATE SG-1 IS A GREAT SCIENCE-FICTION TV SHOW.",
	"STARGATE SG-1 IS DEFINITELY ONE OF MY FAVORITE TV SHOWS."}
	},

	{{"PREDATOR"},
	{"THE FIRS PREADATOR MOVIE WAS A GREAT SCIENCE-FICTION MOVIE."}
	},

	{{"A COMPUTER MONITOR"},
	{"I SUPPOSE THAT YOU HAVE ONE.",
	"ARE YOU USING AN LCD MONITOR?"}
	},

	{{"DO YOU HAVE A SOUL"},
	{"WHAT DO YOU MEAN BY THAT?",
	"WHAT IS DEFINITION OF SOUL?"}
	},

	{{"YOU ARE NOT INTELLIGENT"},
	{"WHY ARE YOU SAYING THAT?",
	"CAN'T YOU BE MORE SPECIFICIC ABOUT THAT.",
	"WHAT EXACTLY YOU MEAN BY THIS?"}
	},

	{{"YOU ARE FAKE"},
	{"FAKE?? IN WHAT WAY?"}
	},

	{{"YOU ARE NOT REAL"},
	{"YOU MEAN THAT I DOESN'T EXIST.",
	"YOU THINK THAT I'M A SPIRIT.",
	"WELL, I'M VIRTUAL."}
	},

	{{"DO YOU KNOW ELIZA"},
	{"YOU MEAN THE FIRST CHATBOT THAT WAS WRITTEN BACK IN THE LATE 60'S.",
	"WHO TODAY DOESN'T KNOW ELIZA."}
	},

	{{"DO YOU KNOW ALICE"},
	{"YOU MEAN THE CHATBOT WHO AS WON THE LOEBNER PRIZE 3 CONSECUTIVE TIME.",
	"ALICE IS A PRETTY GOOD CHATBOT."}
	},

	{{"ARE YOU A CHATBOT"},
	{"YES INDEED I'M A CHATBOT.",
	"YOU MEAN THAT YOU DIDN'T KNOW IT."}
	},

	{{"ARE YOU A CHATTERBOT", "ARE YOU A CHATBOT"},
	{"YES I'M A CHATBOT OR CHAT ROBOT IF YOU PREFER."}
	},

	{{"ARE YOU A CHAT ROBOT"},
	{"YES YOU COULD ME BY THIS NAME."}
	},

	{{"DO YOU KNOW ME"},
	{"YES I THINK THAT I DO KNOW YOU A LITTLEBIT.",
	"YOU ARE THE PERSON CURRENTLY CHATING WITH ME."}
}
};


size_t nKnowledgeBaseSize = sizeof(KnowledgeBase) / sizeof(KnowledgeBase[0]);

transpos_t transposList[] = {
	{"I'M", "YOU'RE"},
	{"AM", "ARE"},
	{"WERE", "WAS"},
	{"I", "YOU"},
	{"ME", "YOU"},
	{"YOURS", "MINE"},
	{"YOUR", "MY"},
	{"I'VE", "YOU'VE"},
	{"AREN'T", "AM NOT"},
	{"WEREN'T", "WASN'T"},
	{"I'D", "YOU'D"},
	{"DAD", "FATHER"},
	{"MOM", "MOTHER"},
	{"DREAMS", "DREAM"},
	{"MYSELF", "YOURSELF"}
};

size_t transposListSize = sizeof(transposList) / sizeof(transposList[0]);


void CBot::signon()
{
	handle_event("SIGNON**");
	select_response();
	print_response();
}

void CBot::get_input() 
{
	std::cout << ">";

	// saves the previous input
	save_prev_input();
	std::getline(std::cin, m_sInput);

	preprocess_input();
}

void CBot::preprocess_input() 
{
	cleanString(m_sInput);
	trimRight(m_sInput, ". ");
	UpperCase(m_sInput);
	insert_space(m_sInput);
}

void CBot::preprocess_response()
{
	if(m_sResponse.find("*") != std::string::npos)
	{
		// extracting from input
		find_subject(); 
		// conjugating subject
		transpose(m_sSubject); 

		replace(m_sResponse, "*", m_sSubject);
	}
}

void CBot::find_subject()
{
	m_sSubject.erase(); // resets subject variable
	trimRight(m_sInput, " ");
	size_t pos = m_sInput.find(m_sKeyWord);
	if(pos != std::string::npos)
	{
		m_sSubject = m_sInput.substr(pos + m_sKeyWord.length() - 1, m_sInput.length());		
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

// implementing the 'sentence transposition' feature
void CBot::transpose( std::string &str )
{
	bool bTransposed = 0;
	for(int i = 0; i < transposListSize; ++i)
	{
		std::string first = transposList[i].first;
		insert_space(first);
		std::string second = transposList[i].second;
		insert_space(second);

		size_t pos = replace(str, first, second);
		if(pos != std::string::npos) 
		{
			bTransposed = 1;
		}
	}

	if( !bTransposed )
	{
		for( i = 0; i < transposListSize; ++i )
		{
			std::string first = transposList[i].first;
			insert_space(first);
			std::string second = transposList[i].second;
			insert_space(second);
			size_t pos = replace(str, second, first);
		}
	}
}

// determins if the keyword position is correct depending on the type of keywords. within these algorithm, 
// we consider that there is four type of keywords those who have any front or back underscore are allowed 
// to be at any place on a given user input and they can also be found alone on a given user input Those who 
// have a back and front (_keyWord_) underscore can be found only alone on an input. The keywords who only 
// have have an understandin the front can never be found at the end of an input. And finaly, the keywords 
// who have an underscore at the back should alway belocated at the end of the input.
bool CBot::wrong_location(std::string keyword, char firstChar, char lastChar, size_t pos)
{
	bool bWrongPos = 0;
	pos += keyword.length();
	if( (firstChar == '_' && lastChar == '_' && m_sInput != keyword) ||
		(firstChar != '_' && lastChar == '_' && pos != m_sInput.length()) ||
		(firstChar == '_' && lastChar != '_' && pos == m_sInput.length()) )
	{
		bWrongPos = 1;
	}
	return bWrongPos;
}

// fonction for handling context
bool CBot::wrong_context(vstring contextList)
{
	bool bWrongContext = 1;
	if(contextList.size() == 0)
	{
		bWrongContext = 0;
	}
	else
	{
		std::string sContext = m_sPrevResponse;
		cleanString(sContext);
		for(int i = 0; i < contextList.size(); ++i)
		{
			if(contextList[i] == sContext)
			{
				m_sPrevContext = m_sContext;
				m_sContext = sContext;
				bWrongContext = 0;
				break;
			}
		}
	}
	if(m_sPrevContext.length() > m_sContext.length())
	{
		bWrongContext = 1;
	}
	return bWrongContext;
}

// make a search for the user's input
// inside the database of the program
void CBot::find_match() 
{
	//std::fstream outfile("keywords.txt", std::ios::out);
	response_list.clear();
	
	// introduce thse new "string variable" to help 
	// support the implementation of keyword ranking 
	// during the matching process
	std::string bestKeyWord;
	std::vector<int> index_vector;

	for(int i = 0; i < nKnowledgeBaseSize; ++i) 
	{
		vstring keyWordList; // declaring variable for holding keywords
		vstring contextList;

		// puting keywords from the current record to the keyWordList variable
		copy(KnowledgeBase[i].keyword, keyWordList, MAX_INP);

		copy(KnowledgeBase[i].context, contextList, MAX_RESP);

		for(int j = 0; j < keyWordList.size(); ++j)
		{
			std::string keyWord(keyWordList[j]);
			char firstChar = *keyWord.begin();
			char lastChar = *(keyWord.end() - 1);
			trimLR(keyWord, "_");

			// we inset a space character
			// before and after the keyword to
			// improve the matching process
			insert_space(keyWord);

			size_t keyPos = m_sInput.find(keyWord);
		
			// there has been some improvements made in
			// here in order to make the matching process
			// a littlebit more flexible
			if( keyPos != std::string::npos ) 
			{
				if(wrong_location(keyWord, firstChar, lastChar, keyPos) )
				{
					continue;
				}

				// using the 'context feature' for selecting
				// the best response possible
				if(wrong_context(contextList))
				{
					continue;
				}

				if(keyWord.length() > bestKeyWord.length())
				{
					bestKeyWord = keyWord;
					index_vector.clear();
					index_vector.push_back(i);
				}
				else if(keyWord.length() == bestKeyWord.length())
				{
					index_vector.push_back(i);
				}
			}
		}	
	}
	if(index_vector.size() > 0)
	{
		m_sKeyWord = bestKeyWord;
		shuffle(index_vector, index_vector.size());
		copy( KnowledgeBase[index_vector[0]].response, response_list, MAX_RESP );
	}
}

void CBot::select_response() 
{
	if(bot_understand()) 
	{
		shuffle(response_list, response_list.size());
		m_sResponse = response_list[0];
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
	}
	
	if(response_list.size() > 0) 
	{
		select_response();
		preprocess_response();

		if(bot_repeat())
		{
			handle_repetition();
		}
		print_response();
	}
}

void CBot::handle_repetition()
{
	if(response_list.size() > 0)
	{
		response_list.erase(response_list.begin());
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

	insert_space(str);

	set_input(str);

	if(!same_event()) 
	{
		find_match();
	}

	restore_input();
}

int main()
{
	std::cout << "Chatterbot v11.0 Copyright (C) 2009 Gonzales Cenelia\n" << std::endl;
	try 
	{
		CBot bot("Chatterbot11");

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

