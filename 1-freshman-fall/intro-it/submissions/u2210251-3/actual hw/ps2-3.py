userInput = input()
i = 0
characters = {
    }
while(i < len(userInput)):
    if(i>0):
        if(userInput[i] == userInput[i-1]):
            characters["" + userInput[i]] +=1 
        else:
            characters["" + userInput[i]] = 1
    else:
        characters["" + userInput[i]] = 1
    i+=1
print(characters)

