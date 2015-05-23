This project makes Howie Chatterbot(http://howie.sourceforge.net/) dynamic by keeping track of the replies and assigning/managing weights of the replies in response to the user statements. 

REQUIREMENTS

Linux OS
Python 3.x
NLTK library (including nltk data) 

NEW SCRIPTS AND FILES ADDED

-preprocess.py (Preprocesses the user input, and stores in dictionary)
-client_ip_processing.py(Actual script that must be run. It takes user input, stores and dynamically manages weights of replies in the dictionary  based on the rating given by user, and finally outputs appropriate reply to the screen)
-Other text files generated which contain mid-process level details.(foo.txt,output.txt,client.txt)
-Details from this files are used in scripts.(female_names,male_names)

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

USAGE

python setup.py	(To install howie)
python preprocess.py
python client_ip_processing.py


To exit, type 'exit'.

NOTE:
If you are not able to run the project,Make sure
1. Python 3 support is enabled
2. NLTK data is downlaoded and can be used by python.(check if import nltk.data works)

Any other issue, please bring to notice.
