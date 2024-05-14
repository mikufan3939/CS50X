from pyfiglet import Figlet
import sys
import random

figlet=Figlet()
fontList=figlet.getFonts()

if(not(len(sys.argv)==1 or len(sys.argv)==3)):
    printf("Invalid Usage")
    sys.exit(1)

if(len(sys.argv)==1):
       figlet.setFont(font=random.choice(fontList))
elif(len(sys.argv)==3 and (sys.argv[1]=="-f" or len(sys.argv[1])=="--font") and sys.argv[2] in fontList):
        font=sys.argv[2]
        figlet.setFont(font=font)
else:
        print("Invalid usage")
        sys.exit(1)

string=input()
print(figlet.renderText(string))






