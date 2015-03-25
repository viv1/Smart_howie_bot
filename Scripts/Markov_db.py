#!/usr/bin/python


# Forms a Markov chain mapping for each sentence in the data_set


from nltk.tokenize import sent_tokenize   #for spliting into sentences
from nltk.tokenize import word_tokenize   #for spliting into words
import pickle
# import random

# class Markov(object):
       
#        def __init__(self, open_file):
#                self.cache = {}
#                self.open_file = open_file
#                self.words = self.file_to_words()
#                self.word_size = len(self.words)
#                self.database()
               
       
#        def file_to_words(self):
#                self.open_file.seek(0)
#                data = self.open_file.read()
#                words = data.split()
#                return words
               
       
#        def triples(self):
#                """ Generates triples from the given data string. So if our string were
#                                "What a lovely day", we'd generate (What, a, lovely) and then
#                                (a, lovely, day).
#                """
               
#                if len(self.words) < 3:
#                        return
               
#                for i in range(len(self.words) - 2):
#                        yield (self.words[i], self.words[i+1], self.words[i+2])
                       
#        def database(self):
#                for w1, w2, w3 in self.triples():
#                        key = (w1, w2)
#                        if key in self.cache:
#                                self.cache[key].append(w3)
#                        else:
#                                self.cache[key] = [w3]
                               
#        def generate_markov_text(self, size=25):
#                seed = random.randint(0, self.word_size-3)
#                seed_word, next_word = self.words[seed], self.words[seed+1]
#                w1, w2 = seed_word, next_word
#                gen_words = []
#                for i in xrange(size):
#                        gen_words.append(w1)
#                        w1, w2 = w2, random.choice(self.cache[(w1, w2)])
#                gen_words.append(w2)
#                return ' '.join(gen_words)


def main():

  
  test_file = open('pp_1_data_1.txt', 'r')

  Markov_db_file = open('output.txt','rwb')

  Markov_dict={}

  chain_len=input("Enter length for Markov chain: ")

  #mark=Markov(test_file)

  #l=mark.generate_markov_text()
  #LIST OF SENTENCES
  for line in test_file:
    sentences=[]      
    #line=replacer.replace(line)    #replacement(like can't with cannot)
    sent=sent_tokenize(line)      #Split into sentences
    #replacer.replace(sent)
    #print(sent)
    for s in sent:
      sentences.append(s)       #Add each sentence to the list of sentences

  #print(sentences)

  #LIST OF WORDS
    for words in sentences:
      tokens=[]   
      word_list=word_tokenize(words)    #Split into words

      for w in word_list:

        tokens.append(w)        #Add each sentence to the list of words

    #print(tokens)

  #STOPWORDS REMOVAL
    punctuations=['.',',',"'",'?']  # '?' to be used or not
    
    tokens=[w for w in tokens if w not in punctuations]
    
    #print(tokens)
    #print(len(tokens))
    length=len(tokens)

#CREATING A MARKOV DICTIONARY, GIVEN THE CHAIN_LENGTH

    if length< chain_len+1:
      continue
    else:
      
      for i in xrange(length-chain_len):

        key=tuple(tokens[i:i+chain_len])


        if key not in Markov_dict:                  # If key is unique(first time) 
          mapped_into=[]
          mapped_into.append(tokens[i+chain_len])
    
          Markov_dict[key]=mapped_into
          #print(Markov_dict)
        else:                                       # If key has already come up atleast once
          Markov_dict[key].append(tokens[i+chain_len])  # append to existing set of items for the keys

  print(Markov_dict)  
  #pickle.dump(Markov_dict,Markov_db_file)
  #kklk=pickle.load(Markov_db_file)
  #print(kklk)

main()