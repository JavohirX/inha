digits = ""
letter = ""
i = 0
userInput = input()
while( i < len(userInput)):
    if(str.isdigit(userInput[i]) == True):
        digits += userInput[i]
    else:
        letter = userInput[i]
        print(int(digits) * letter, end = ')
        digits = ""
    i+=1