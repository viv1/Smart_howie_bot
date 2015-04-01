#!/usr/bin/python

from __future__ import division
# Takes input from user and preprocesses it

from nltk.tokenize import sent_tokenize		#for spliting into sentences
from nltk.tokenize import word_tokenize		#for spliting into words

from nltk.corpus import stopwords
from nltk.corpus import wordnet
from nltk.corpus import names


import subprocess
import os
import re
import random
import pickle


training_mode = 1
flag = 0
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

#Selects and returns a statement(and it's location) based on it's weights
def select_stat(Mapping,Weights,toks):
	total_sum=0
	x=0
	for w in Weights[toks]:
		total_sum=total_sum+Weights[toks][x]		#Find total sum of weights 
		x=x+1

	prob_val=random.random()*total_sum				#Random no. in the appropriate range

	x=0
	partial_sum=0
	for w in Weights[toks]:
		partial_sum=partial_sum+Weights[toks][x]	#Decide which statement to select 
		if prob_val <= partial_sum:
			#Weights[toks][x] = Weights[toks][x]+1	#For Updating the weight of selected statement 
			return (Mapping[toks][x],x)				#returns in tuple form...(sent,loc)
			#break
		else:
			x=x+1

	#print(total_sum)

#tuple1=('link','crow','rat')
#tuple2=('ring','bear','owl')

def Wordnet_sim(tuple1,tuple2):

	count_members=0
	total_sim=0
	sim_val=0

	for t1 in tuple1:
		count_members=count_members+1
		max_sim=0
		try:
			from1=wordnet.synsets(t1)[0]
			
		except:
			count_members=count_members-1
			continue
			
		
		for t2 in tuple2:
			try:

				from2=wordnet.synsets(t2)[0]
			except:
				continue
			max_sim=max(max_sim,from1.wup_similarity(from2))
			
		total_sim=total_sim+max_sim

	sim_val=total_sim/count_members
	return sim_val



#Update when not in Mapping db
def add_to_db(Mapping,Weights,toks,eliza_stat):	
	mapped_into=[]
	mapped_into.append(eliza_stat)
	Mapping[toks]=mapped_into	

	weight=[]
	weight.append(1)
	Weights[toks]=weight




# Update Weights....
def update_weight(Weights,toks,loc,rating_val):
	if rating_val>5:
		normalised_val=(rating_val-5)*(rating_val-5)
	else:
		normalised_val=(rating_val-5)*(5-rating_val)

	Weights[toks][loc]=Weights[toks][loc]+normalised_val		#Update weight



#DEFINITION OF MAIN
def func(input_string):
	


				# if 1, in training mode
#	training_mode=input("Training mode(1) or Actual mode(0): ")

#	while training_mode!=0 and training_mode!=1:
#		training_mode=input("Training mode(1) or Actual mode(0): ")
		
#	while 1:
	client_says= input_string
	#print(client_says)

	#replacer=RegexpReplacer()
	#replacer.replace("can't is a contraction")


	with open('output.txt', 'rb') as handle:
		Mapping = pickle.loads(handle.read())
	with open('weights.txt', 'rb') as handle:
		Weights = pickle.loads(handle.read())
	
	#print(Mapping)
#LIST OF WORDS

	tokens=[]		
	word_list=word_tokenize(client_says)		#Split into words

	for w in word_list:

		tokens.append(w.lower())				#Add each sentence to the list of words

#print(tokens)

#STOPWORDS REMOVAL
	english_stops=set(stopwords.words('english')) #Edit stopwords
	punctuations=['.',',',"'",'?']	# '?' to be used or not
	female_names=names.words('female.txt')
	for fe in female_names:
		fe=fe.lower()
	male_names=names.words('male.txt')
	for mal in male_names:
		mal=mal.lower()

	tokens=[w for w in tokens if w not in english_stops]
	tokens=[w for w in tokens if w not in punctuations]
	#Replace not rename
	#tokens=[w for w in tokens if w not in female_names]
	#tokens=[w for w in tokens if w not in male_names]



	tokens = [x if (x not in male_names) else "Name" for x in tokens]
	tokens = [x if (x not in female_names) else "Name" for x in tokens]


	
	toks=tuple(tokens)

	eliza_needed=1

	if toks in Mapping:
		eliza_needed=0
		ok=select_stat(Mapping,Weights,toks)
		print("Coun: "+ok[0])							#ok[0] is the reply
		if training_mode==1:
			rating=input("Rate the response: ")
			update_weight(Weights,toks,ok[1],rating)		#ok[1] is the location of selected statement in list
		
	else:
		for ma in Mapping:
			if Wordnet_sim(toks,ma) > 0.6:
				eliza_needed=0
				ok=select_stat(Mapping,Weights,ma)
				print("Coun: "+ok[0])
				if training_mode==1:
					rating=input("Rate the response: ")
					if rating > 5:
						add_to_db(Mapping,Weights,ma,ok[0])
				break
					

	#if not in database...go to Howie
	if eliza_needed==1:

		with open("../Howie/howie-code/client.txt", "wb") as fo:
			fo.write(client_says)
	#imp closing the file here..since writes to a file on close
			#fo.write(client_says)

		p=subprocess.call(['python','../Howie/howie-code/runme.py'])

		with open("../Howie/howie-code/foo.txt", "r") as outp:
			bot_says=outp.read()
			#return "Coun: "+bot_says

		if training_mode==1:
			rating=input("Rate the response: ")
			if rating > 5:
				add_to_db(Mapping,Weights,toks,bot_says)
			pass

		#bot_says=outp.read() 
		#print("Coun: "+bot_says)    

#Update the database files
		   

		#p=subprocess.Popen(['python','runme.py'],stdin=subprocess.PIPE,stdout=subprocess.PIPE,bufsize=1)
	
		with open('output.txt', 'wb') as handle:
			pickle.dump(Mapping, handle)

		with open('weights.txt', 'wb') as handle:
			pickle.dump(Weights, handle)

		return bot_says
	#if toks in Mapping:
	#	print "yeah"
		
	#print(Mapping)
	# for tok in toks:
	# 	for syn in wordnet.synsets(tok):
	# 		for keys in Mapping:
	# 			pass


from Tkinter import *
    
   
def main():
    root = Tk()
    frame=Frame(root)
    frame.pack()


    textPad=Frame(frame)
    text=Text(textPad,height=20,width=50)
    # add a vertical scroll bar to the text area
    scroll=Scrollbar(textPad)
    text.configure(yscrollcommand=scroll.set)
    text.pack(side=LEFT)
    text.insert("0.0","Training mode(1) or Actual mode(0): ")
    scroll.pack(side=RIGHT,fill=Y)
    textPad.pack(side=TOP)
    text1 = Text(frame,height = 3,width = 50)
    text1.pack(side = BOTTOM)

    def screenshot(*ignore): os.system("screencapture -s %s" % check_snapshot) 
    
    def callback(event):
        global flag
        if flag == 0:
        	training_mode = text1.get("0.0", "end-1c")
        	text1.delete("0.0", "end-1c")
        	text.delete("0.0", "end-1c")
        	flag = 1
        else:
	        print "clicked at"
	        text.insert("0.0",text1.get("0.0", "end-1c"))
	        text.insert("0.0",text1.get("0.0", func(text1.get("0.0", "end-1c"))))
	        #text.insert("0.0",)
	        text1.delete("0.0", "end-1c")
	    
    
    root.bind('<Return>',callback)       
    root.mainloop()

main()


