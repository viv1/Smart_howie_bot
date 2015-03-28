from Tkinter import *
    
def cb():
    print "enter"
    
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
    scroll.pack(side=RIGHT,fill=Y)
    textPad.pack(side=TOP)
    text1 = Text(frame,height = 3,width = 50)
    text1.pack(side = BOTTOM)

    def screenshot(*ignore): os.system("screencapture -s %s" % check_snapshot) 

    def callback(event):
        print "clicked at"
        text.insert("0.0",text1.get("0.0", "end-1c"))
        text.insert("0.0",)
        text1.delete("0.0", "end-1c")
    
    root.bind('<Return>',callback)       
    root.mainloop()

main()


