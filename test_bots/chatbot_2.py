#chatbot replies dependent upon certain sentences
#The replies should match the case and order to get a reply from the database

#Added "BYE" and "Don't know" ability

from random import randint
def main():
	
	KnowledgeBase={"WHAT IS YOUR NAME" : ["MY NAME IS CHATTERBOT2.",
     "YOU CAN CALL ME CHATTERBOT2.",
     "WHY DO YOU WANT TO KNOW MY NAME?"],
     "HI": 
    ["HI THERE!",
     "HOW ARE YOU?",
     "HI!"]
    ,
    "HOW ARE YOU":
    ["I'M DOING FINE!",
    "I'M DOING WELL AND YOU?",
    "WHY DO YOU WANT TO KNOW HOW AM I DOING?"]
    ,
    "WHO ARE YOU":
    ["I'M AN A.I PROGRAM.",
     "I THINK THAT YOU KNOW WHO I'M.",
     "WHY ARE YOU ASKING?"]
    ,
    "ARE YOU INTELLIGENT":
    ["YES,OFCORSE.",
     "WHAT DO YOU THINK?",
     "ACTUALY,I'M VERY INTELLIGENT!"]
    ,
    "ARE YOU REAL":
    ["DOES THAT QUESTION REALLY MATERS TO YOU?",
     "WHAT DO YOU MEAN BY THAT?",
     "I'M AS REAL AS I CAN BE."]
    }
        
	while(1):
		user_says=input()
		k=randint(0,2)
		print(k)
		if user_says in KnowledgeBase:
			print(KnowledgeBase[user_says][k])
		elif user_says=="BYE":
			print("IT WAS NICE TALKING TO YOU USER, SEE YOU NEXT TIME!")
			break
		else :
			print("I'M NOT SURE IF I  UNDERSTAND WHAT YOU ARE TALKING ABOUT.")
			
			
			
			
main()	
