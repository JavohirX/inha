j = 1
while(j>0):
    userInput = float(input())
    i = 0
    positiveNum = userInput
    negativeNum = 0.0
    ans = (negativeNum + positiveNum)/2.0
    while(i>=0):
        if(abs(ans**3 - userInput) <= 0.0001):
            print("Answer is: " + str(ans) + "\n")
            print("Number of iterations are: " + str(i) + "\n")
            break
        ans = (negativeNum + positiveNum)/2.0
        if((ans**3 - userInput) >= 0):
            positiveNum = ans
        elif((ans**3 - userInput**3) < 0):
            negativeNum = ans
        i+=1