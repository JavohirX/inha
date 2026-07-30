word = input('Enter some word \n')
i = 0
isThereLower = 'no lowercase'
while(i < (len(word) - 1)):
    if(word[i] == word[i].lower()):
        isThereLower = 'lowercase'
        break
    i+=1
print('There is ' + isThereLower)
