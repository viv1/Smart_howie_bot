import subprocess

def main():

	p=subprocess.Popen(['python','runme.py'],stdin=subprocess.PIPE,stdout=subprocess.PIPE,bufsize=1)

	p.stdin.write("Hi. How are you?")
	p.kill()

	#outp=p.stdout.readline()
	#print outp

main()