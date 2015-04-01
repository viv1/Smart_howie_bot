#very basic chatbot
#replies randomly from the given database

from random import randint
def main():
	Response=["I HEARD YOU!",					#Response database
        "SO, YOU ARE TALKING TO ME.",
        "CONTINUE, I’M LISTENING.",
        "VERY INTERESTING CONVERSATION.",
        "TELL ME MORE..."]
        
    
	k=1;
	while(1):
		k=randint(0,4)		#Use any random no generator algo here.
		ques=input()
		print(Response[k])
		

main()
