greeting=input("Greeting: ")

greeting=greeting.lower().strip()

if greeting.find("hello")==0:
    print("$0", end="")
elif greeting[0]=='h':
    print("$20", end="")
else:
    print("$100", end="")
