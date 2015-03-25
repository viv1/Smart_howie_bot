#!/usr/bin/python

# Takes input from user and preprocesses it

from nltk.tokenize import sent_tokenize		#for spliting into sentences
from nltk.tokenize import word_tokenize		#for spliting into words

from nltk.corpus import stopwords

import re

replacement_patterns = [
(r'won\'t', 'will not'),
(r'can\'t', 'cannot'),
(r'i\'m', 'i am'),
(r'ain\'t', 'is not'),
(r'(\w+)\'ll', '\g<1> will'),
(r'(\w+)n\'t', '\g<1> not'),
(r'(\w+)\'ve', '\g<1> have'),
(r'(\w+)\'s', '\g<1> is'),
(r'(\w+)\'re', '\g<1> are'),
(r'(\w+)\'d', '\g<1> would')
]


#REPLACEMENT 
class RegexpReplacer(object):
	def __init__(self, patterns=replacement_patterns):
		self.patterns = [(re.compile(regex), repl) for (regex, repl) in patterns]

	def replace(self, text):
		s = text
		for (pattern, repl) in self.patterns:
			s = re.sub(pattern, repl, s)
		return s


#DEFINITION OF MAIN
def main():
	
	
	client_says=raw_input("You: ")

	#replacer=RegexpReplacer()
	#replacer.replace("can't is a contraction")

	i=0
	#mapping={}


	

#LIST OF WORDS

	tokens=[]		
	word_list=word_tokenize(client_says)		#Split into words

	for w in word_list:

		tokens.append(w)				#Add each sentence to the list of words

#print(tokens)

#STOPWORDS REMOVAL
	english_stops=set(stopwords.words('english')) #Edit stopwords
	punctuations=['.',',',"'",'?']	# '?' to be used or not
	tokens=[w for w in tokens if w not in english_stops]
	tokens=[w for w in tokens if w not in punctuations]
	toks=tuple(tokens)
	print(toks)	


main()