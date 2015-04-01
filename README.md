This project is a personal side project aimed at understanding the working of git and github as well as understanding concepts like NLP, ML, AI, DM among others.

The aim is to create an AI chatbot which will act as a counselor.

IMPLEMENTATION

The bot has 2 modes(Training and Actual mode)

The project has two levels of logic.

On level 1,
Based on actual transcripts, a database of mapping of set of keywords(after preprocessing) to actual sentences is created. Each sentence has a weight associated with it.

On level 2, 
Answers given by Howie Chatterbot(http://howie.sourceforge.net/).


Using preprocess.py, the database of mapping of sets of keywords to actual replies by counsellor is created.

When user enters any statement, the statement is preprocessed and the set of keywords thus obtained is searched in the database. If found, the bot replies the mapped sentence as response. Otherwise, it goes to howie for response. The response given by howie is given as reply.

In training mode, after each reply the user is supposed to give a rating (0-10), based on which the weight of response is changed.

In actual mode, no rating needs to be given.

Currently, A deliberate lag is shown to indicate that the answer is given by howie.

