import re
from cs50 import get_int
from sys import exit

amex = ["34", "37"]
visa = ["4"]
mastercard = ["51", "52", "53", "54", "55"]
validSizes = [13, 15, 16]
checksum = 0
flag = ""
number = input("Number: ")

validDigit = re.search("^35|^37|^[5][1-5]|^4", number)

if (validDigit != None and len(validDigit.string) in validSizes):
    if len(number) == 15 and validDigit.group() in amex:
        flag = "AMEX"
    elif len(number) == 16 and validDigit.group() in mastercard:
        flag = "MASTERCARD"
    elif (len(number) == 16 or len(number) == 13) and validDigit.group() in visa:
        flag = "VISA"
    else:
        print("INVALID")
        exit(1)
else:
    print("INVALID")
    exit(1)

aux = 0
for i in range(len(number), 0, -1):
    if aux % 2 == 1:
        if int(number[i-1])*2 < 10:
            checksum = checksum+(int(number[i-1])*2)
        else:
            checksum = checksum+((int(number[i-1])*2) % 10)+1
    else:
        checksum = checksum+int(number[i-1])
    aux = aux+1

if checksum % 10 == 0:
    print(flag)
else:
    print("INVALID")
    exit(0)
