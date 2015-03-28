#!/usr/bin/python

# Forms a Mapping of tokens of clients to that of counselor

from nltk.tokenize import sent_tokenize		#for spliting into sentences
from nltk.tokenize import word_tokenize		#for spliting into words

from nltk.corpus import stopwords
from nltk.corpus import names

import re

# from cStringIO import StringIO
# import sys
import pickle							# To store dictionary object in file

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

#DEFINE SUM

def sum(object,num):
	num=num*2
	#print("yowzee")
	return num




#We need to replace names with 'NAME'. Ask user for name.

#DEFINITION OF MAIN
def main():
	
	test_file = open('newdata.txt', 'r')
	
	#replacer=RegexpReplacer()
	#replacer.replace("can't is a contraction")

	i=0
	Mapping={}
	Weights={}


#LIST OF SENTENCES
	for line in test_file:
		sentences=[]			
		#line=replacer.replace(line)		#replacement(like can't with cannot)
		sent=sent_tokenize(line)			#Split into sentences
		#replacer.replace(sent)
		#print(sent)
		for s in sent:
			sentences.append(s)				#Add each sentence to the list of sentences

	#print(sentences)

	#LIST OF WORDS
		for words in sentences:
			tokens=[]		
			word_list=word_tokenize(words)		#Split into words

			for w in word_list:
				tokens.append(w.lower())				#Add each sentence to the list of words

		#print(tokens)

	#STOPWORDS REMOVAL
		english_stops=set(stopwords.words('english')) #Edit stopwords
		english_stops.remove('i')
		english_stops.remove('you')
		punctuations=['.',',',"'",'?','(',')']	# '?' to be used or not
		female_names=names.words('female.txt')
		for fe in female_names:
			fe=fe.lower()
		male_names=names.words('male.txt')
		for mal in male_names:
			mal=mal.lower()

		tokens=[w for w in tokens if w not in english_stops]
		tokens=[w for w in tokens if w not in punctuations]

		#Rename(not remove) names to 'Name'
		#tokens=[w for w in tokens if w not in female_names]
		#tokens=[w for w in tokens if w not in male_names]

		if i%2==0:
			client_token=tokens
		else:
			key=tuple(client_token)
			if key not in Mapping:

				mapped_into=[]
				mapped_into.append(line)
				Mapping[key]=mapped_into	#tuple because Mapping from immutable keys only
				#print(tokens)	
			else:

				Mapping[key].append(line)


		
		i=i+1
			# for y in xrange(0,x):
			# 	sum_= sum_+Weights[m][y]
			# weight.append(sum_)

	for m in Mapping:					#Initialize with weight 1
		weight=[]
		x=0								#To remember location in list
		for k in Mapping[m]:
			weight.append(1)
			Weights[m]=weight
			x=x+1
	
	print(Mapping) 
	print(Weights)
	#print(sum(Mapping,5))
	with open('output.txt', 'wb') as handle:
		pickle.dump(Mapping, handle)

	with open('weights.txt', 'wb') as handle:
		pickle.dump(Weights, handle)
	

main()