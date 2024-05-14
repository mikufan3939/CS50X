from cs50 import get_string
from re import findall
from sys import exit

text = get_string("Text: ")
numberLetters = 0
numberWords = 0
numberSentences = 0

for i in text:
    if i.isalpha():
        numberLetters += 1
    if i.isspace():
        numberWords += 1
    if i == "." or i == "?" or i == "!":
        numberSentences += 1

if numberWords > 0:
    numberWords += 1
    l = numberLetters/(numberWords/100)
    s = numberSentences/(numberWords/100)
    index = 0.0588*l-0.296*s-15.8
else:
    exit(1)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
